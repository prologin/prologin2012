#include <fstream>
#include <map>
#include <set>

#include "rules.hh"

#include <utils/log.hh>
#include <utils/buffer.hh>
#include <rules/player.hh>

#include "constant.hh"
#include "game.hh"
#include "map.hh"

#include "action-move.hh"
#include "action-attack.hh"

Rules::Rules(const rules::Options& opt)
    : opt_(opt),
      champion_(nullptr),
      sandbox_(opt.time)
{
    // Load map from file
    std::ifstream ifs(opt.map_name);

    Map* map = new Map();
    map->load(ifs);

    GameState* game_state = new GameState(map, opt.players);

    game_state->init();

    api_ = new Api(game_state, opt.player);

    // Get the champion library if we are a client
    if (!opt.champion_lib.empty())
    {
        champion_ = new utils::DLL(opt.champion_lib);

        champion_partie_init = champion_->get<f_champion_partie_init>("partie_init");
        champion_jouer_placement = champion_->get<f_champion_jouer_placement>("jouer_placement");
        champion_jouer_deplacement = champion_->get<f_champion_jouer_deplacement>("jouer_deplacement");
        champion_jouer_attaque = champion_->get<f_champion_jouer_attaque>("jouer_attaque");
        champion_partie_fin = champion_->get<f_champion_partie_fin>("partie_fin");

        // Caml corner case
        typedef void (*caml_init)(char**);
        caml_init caml_startup = champion_->get<caml_init>("caml_startup");

        if (caml_startup != nullptr)
            caml_startup(nullptr);

        sandbox_.execute(champion_partie_init);
    }

    players_ = opt.players;

    // Register Actions
    api_->actions()->register_action(ACTION_MOVE,
            []() -> rules::IAction* { return new ActionMove(); });
    api_->actions()->register_action(ACTION_ATTACK,
            []() -> rules::IAction* { return new ActionAttack(); });
}


// a bit ugly, but used to test
Rules::Rules(rules::Players_sptr players, Api* api)
    : champion_(nullptr),
      api_(api),
      players_(players),
      sandbox_()
{
    // Register Actions
    api_->actions()->register_action(ACTION_MOVE,
            []() -> rules::IAction* { return new ActionMove(); });
    api_->actions()->register_action(ACTION_ATTACK,
            []() -> rules::IAction* { return new ActionAttack(); });
}

Rules::~Rules()
{
    if (champion_)
    {
        sandbox_.execute(champion_partie_fin);
        delete champion_;
    }

    delete api_;
}

void Rules::client_loop(rules::ClientMessenger_sptr msgr)
{
    CHECK(champion_ != nullptr);

    game_phase phase;

    while (!is_finished())
    {
        DEBUG("TURN %d", api_->game_state()->getCurrentTurn());

        phase = api_->game_state()->getPhase();

        api_->actions()->clear();

        switch (phase)
        {
        case PHASE_PLACEMENT:
            sandbox_.execute(champion_jouer_placement);
            break;
        case PHASE_DEPLACEMENT:
            sandbox_.execute(champion_jouer_deplacement);
            break;
        case PHASE_ATTAQUE:
            sandbox_.execute(champion_jouer_attaque);
            break;
        }

        DEBUG("sending");
        // Send actions
        msgr->send_actions(*api_->actions());
        DEBUG("wait4ack");
        msgr->wait_for_ack();
        DEBUG("ack ok");

        api_->actions()->clear();

        // Receive actions
        DEBUG("pull");
        msgr->pull_actions(api_->actions());
        DEBUG("pulled");

        // Apply them onto the gamestate
        for (auto& action : api_->actions()->actions())
        {
            api_->game_state_set(action->apply(api_->game_state()));
        }

        DEBUG("resolving %d", phase);
        switch (phase)
        {
        case PHASE_PLACEMENT:
            resolve_moves();
            resolve_end_of_placement_turn();
            break;
        case PHASE_DEPLACEMENT:
            resolve_moves();
            resolve_end_of_deplacement_phase();
            break;
        case PHASE_ATTAQUE:
            for (rules::Player_sptr player: players_->players)
                api_->game_state()->deactivateElfeVision(player->id - 1);

            resolve_attacks();
            resolve_points();
            resolve_end_of_attaque_phase();
            break;
        }
        DEBUG("end resolving");
    }

    DEBUG("winner = %i", winner_);
}

void Rules::server_loop(rules::ServerMessenger_sptr msgr)
{
    CHECK(champion_ == nullptr);

    rules::Actions actions;
    game_phase phase;

    while (!is_finished())
    {
        DEBUG("TURN %d", api_->game_state()->getCurrentTurn());

        phase = api_->game_state()->getPhase();

        api_->actions()->clear();

        for (uint32_t i = 0; i < players_->players.size(); ++i)
        {
            // Receive actions
            msgr->recv_actions(api_->actions());

            // Apply them onto the gamestate
            for (auto& action : api_->actions()->actions())
            {
                api_->game_state_set(action->apply(api_->game_state()));
                actions.add(action);
            }

            DEBUG("acked");
            msgr->ack();
        }

        DEBUG("resolving %d", phase);
        switch (phase)
        {
        case PHASE_PLACEMENT:
            resolve_moves();
            resolve_end_of_placement_turn();
            break;
        case PHASE_DEPLACEMENT:
            resolve_moves();
            resolve_end_of_deplacement_phase();
            break;
        case PHASE_ATTAQUE:
            for (rules::Player_sptr player: players_->players)
                // - 1 because stechec assigns id starting from 1
                api_->game_state()->deactivateElfeVision(player->id - 1);

            resolve_attacks();
            resolve_points();
            resolve_end_of_attaque_phase();
            break;
        }

        // Send actions
        DEBUG("sending");
        msgr->push_actions(actions);
        DEBUG("sent");
        actions.clear();
    }

    DEBUG("winner = %i", winner_);
}

void Rules::resolve_moves()
{
    DEBUG("resolve_moves");
    auto& pendingMoves = api_->game_state()->getPendingMoves();

    for (auto unit : api_->game_state()->getUnits())
        unit->resetPenombre();

    if (pendingMoves.size() == 0)
      return;

    for (auto& moves : pendingMoves)
    {
        for (auto& move : moves)
        {
            Unit_sptr unit = api_->game_state()->getUnit(move.second->getUnitInfo());
            api_->game_state()->getMap()->moveUnit(unit->getUnitInfo(),
                        unit->getPosition(), move.first);
            unit->setPosition(move.first);
            unit->setOrientation(Map::getOrientation(move.first,
                        unit->getPosition()));
        }
        for (auto unit : api_->game_state()->getUnits())
            unit->addPenombre(
                    api_->game_state()->getMap()->getSurroundings(
                        unit->getPosition(),
                        unit->getOrientation(), unit->getVision()));
    }
    // It's kind of ugly but we're running out of time
    for (auto& move : pendingMoves[0])
        move.second->applyDirection(api_->game_state());
    for (auto& moves : pendingMoves)
        moves.clear();
}

void Rules::resolve_attacks()
{
    DEBUG("resolve_attacks");
    auto& pendingAttacks = api_->game_state()->getPendingAttacks();
    auto& pendingBastoooon = api_->game_state()->getPendingBastoooon();
    std::map<int, int> markedUnits;

    for (auto& attack : pendingAttacks)
    {
        if (attack->getType() != ATTAQUE_FUS_RO_DAH)
          break;
        attack->markFusRoDah(api_->game_state(), markedUnits);
    }
    for (auto& attack : pendingAttacks)
        attack->applyAttack(api_->game_state());
    for (auto& attack : pendingBastoooon)
        api_->game_state()->getUnit(attack->getPersoInfo())->saveLife();
    for (auto& attack : pendingBastoooon)
        attack->applyBastoooon(api_->game_state());

    pendingAttacks.clear();
    pendingBastoooon.clear();
}

void Rules::resolve_points()
{
    DEBUG("resolve_points");
    GameState* st = api_->game_state();

    for (auto unit : st->getUnits())
    {
        if (!unit->isDead())
            continue;

        // Unit is dead
        unsigned int teamkill = 0;
        for (unit_info attacker : unit->getAttackers())
            if (attacker.player_id == unit->getPlayer())
                ++teamkill;

        // Only teamkill
        if (teamkill == unit->getAttackers().size())
            api_->player()->score -= 1;
        // no teamkill, every team get a point
        else if (teamkill == 0)
        {
            std::set<int> attackers_team;
            for (unit_info attacker : unit->getAttackers())
                attackers_team.insert(attacker.player_id);

            for (int team : attackers_team)
                players_->players[team]->score += 1;
            players_->players[unit->getPlayer()]->score -= 1;
        }
            // else
            // mixed teamkill and offensive kill
            // no points given

        // reset life & cooldowns
        unit->respawn();

        // Move unit to spawn position
        st->getMap()->moveUnit(unit->getUnitInfo(), unit->getPosition(),
            unit->getSpawn());
    }
}

void Rules::resolve_end_of_placement_turn()
{
    GameState* st = api_->game_state();
    Map* map = st->getMap();

    INFO("end of placement turn %d", st->getCurrentTurn());

    st->incrementTurn();

    if (st->getCurrentTurn() == map->getPlacementTurns())
    {
        INFO("end of placement phase");
        st->setPhase(PHASE_DEPLACEMENT);

        // End of placement phase
        // Save spawns
        for (auto unit : st->getUnits())
            unit->setSpawn(unit->getPosition());
    }
}

void Rules::resolve_end_of_deplacement_phase()
{
    GameState* st = api_->game_state();

    INFO("end of move phase %d", st->getCurrentTurn());

    st->setPhase(PHASE_ATTAQUE);
}

void Rules::resolve_end_of_attaque_phase()
{
    GameState* st = api_->game_state();

    INFO("end of attack phase %d", st->getCurrentTurn());

    st->incrementTurn();
    st->setPhase(PHASE_DEPLACEMENT);

    for (Unit_sptr unit : st->getUnits())
        unit->resetAttackers();
}

bool Rules::is_finished()
{
    return api_->game_state()->isFinished();
}
