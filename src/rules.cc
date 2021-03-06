#include <fstream>
#include <map>
#include <set>

#include "rules.hh"

#include <rules/player.hh>
#include <utils/buffer.hh>
#include <utils/log.hh>

#include "constant.hh"
#include "game.hh"
#include "map.hh"

#include "action-ack.hh"
#include "action-attack.hh"
#include "action-move.hh"

Rules::Rules(const rules::Options& opt)
    : opt_(opt), champion_(nullptr), sandbox_(opt.time)
{
    // Load map from file
    std::ifstream ifs(opt.map_file);

    Map* map = new Map();
    map->load(ifs);

    auto game_state = std::make_unique<GameState>(map, opt.players);
    game_state->init();

    int equipe = 0;
    if (opt.player.get() != nullptr)
    {
        for (; (unsigned)equipe < opt.players.size(); ++equipe)
            if (opt.players[equipe]->id == opt.player->id)
                break;
    }

    api_ = std::make_unique<Api>(std::move(game_state), opt.player, equipe);

    // Get the champion library if we are a client
    if (!opt.champion_lib.empty())
    {
        champion_ = std::make_unique<utils::DLL>(opt.champion_lib);

        champion_partie_init =
            champion_->get<f_champion_partie_init>("partie_init");
        champion_jouer_placement =
            champion_->get<f_champion_jouer_placement>("jouer_placement");
        champion_jouer_deplacement =
            champion_->get<f_champion_jouer_deplacement>("jouer_deplacement");
        champion_jouer_attaque =
            champion_->get<f_champion_jouer_attaque>("jouer_attaque");
        champion_partie_fin =
            champion_->get<f_champion_partie_fin>("partie_fin");

        if (opt.player->type == rules::SPECTATOR)
            champion_partie_init();
        else
            sandbox_.execute(champion_partie_init);
    }

    players_ = opt.players;
    spectators_ = opt.spectators;
    timeout_ = opt.time;

    // Register Actions
    api_->actions()->register_action(
        ACTION_MOVE, []() { return std::make_unique<ActionMove>(); });
    api_->actions()->register_action(
        ACTION_ATTACK, []() { return std::make_unique<ActionAttack>(); });
    api_->actions()->register_action(
        ACTION_ACK, []() { return std::make_unique<ActionAck>(); });
    playerActions_.register_action(
        ACTION_MOVE, []() { return std::make_unique<ActionMove>(); });
    playerActions_.register_action(
        ACTION_ATTACK, []() { return std::make_unique<ActionAttack>(); });
    playerActions_.register_action(
        ACTION_ACK, []() { return std::make_unique<ActionAck>(); });
}

// a bit ugly, but used to test
Rules::Rules(const rules::Players& players, std::unique_ptr<Api> api)
    : champion_(nullptr), api_(std::move(api)), players_(players), sandbox_()
{
    // Register Actions
    api_->actions()->register_action(
        ACTION_MOVE, []() { return std::make_unique<ActionMove>(); });
    api_->actions()->register_action(
        ACTION_ATTACK, []() { return std::make_unique<ActionAttack>(); });
    api_->actions()->register_action(
        ACTION_ACK, []() { return std::make_unique<ActionAck>(); });
    playerActions_.register_action(
        ACTION_MOVE, []() { return std::make_unique<ActionMove>(); });
    playerActions_.register_action(
        ACTION_ATTACK, []() { return std::make_unique<ActionAttack>(); });
    playerActions_.register_action(
        ACTION_ACK, []() { return std::make_unique<ActionAck>(); });
}

Rules::~Rules()
{
    if (champion_)
    {
        if (opt_.player->type == rules::SPECTATOR)
            champion_partie_fin();
        else
            sandbox_.execute(champion_partie_fin);
    }
}

void Rules::player_loop(rules::ClientMessenger_sptr msgr)
{
    CHECK(champion_ != nullptr);

    game_phase phase;

    while (!is_finished())
    {
        INFO("TURN %d", api_->game_state().getCurrentTurn());

        phase = api_->game_state().getPhase();

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

        // Send actions
        DEBUG("sending");
        msgr->send_actions(*api_->actions());
        msgr->wait_for_ack();
        DEBUG("ack");

        api_->actions()->clear();

        // Receive actions
        DEBUG("pull %d actions", api_->actions()->size());
        msgr->pull_actions(api_->actions());
        DEBUG("pulled %d actions", api_->actions()->size());

        // Apply them onto the gamestate
        for (const auto& action : api_->actions()->all())
        {
            DEBUG("Applying action");
            api_->game_state_apply(*action);
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
            for (uint32_t i = 0; i < players_.size(); ++i)
                api_->game_state().deactivateElfeVision(i);

            resolve_attacks();
            resolve_points();
            resolve_end_of_attaque_phase();
            break;
        }
        DEBUG("end resolving");
    }

    DEBUG("winner = %i", winner_);
}

void Rules::spectator_loop(rules::ClientMessenger_sptr msgr)
{
    CHECK(champion_ != nullptr);

    rules::Actions actions;
    game_phase phase;

    while (!is_finished())
    {
        INFO("TURN %d", api_->game_state().getCurrentTurn());

        phase = api_->game_state().getPhase();

        api_->actions()->clear();

        // No sandbox: spectators can't timeout
        switch (phase)
        {
        case PHASE_PLACEMENT:
            champion_jouer_placement();
            break;
        case PHASE_DEPLACEMENT:
            champion_jouer_deplacement();
            break;
        case PHASE_ATTAQUE:
            champion_jouer_attaque();
            break;
        }

        api_->actions()->clear();
        api_->actions()->add(std::make_unique<ActionAck>(api_->player()->id));

        // Send actions
        msgr->send_actions(*api_->actions());
        msgr->wait_for_ack();

        api_->actions()->clear();

        // Receive actions
        msgr->pull_actions(api_->actions());

        // Apply them onto the gamestate
        for (const auto& action : api_->actions()->all())
        {
            api_->game_state_apply(*action);
        }

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
            for (uint32_t i = 0; i < players_.size(); ++i)
                api_->game_state().deactivateElfeVision(i);

            resolve_attacks();
            resolve_points();
            resolve_end_of_attaque_phase();
            break;
        }
    }
}

void Rules::server_loop(rules::ServerMessenger_sptr msgr)
{
    CHECK(champion_ == nullptr);

    rules::Actions actions;
    game_phase phase;

    uint32_t size = players_.size() + spectators_.size();

    std::vector<bool> last_turn_players(players_.size(), true);
    std::vector<bool> turn_players(players_.size(), false);

    while (!is_finished())
    {
        INFO("TURN %d", api_->game_state().getCurrentTurn());

        phase = api_->game_state().getPhase();

        api_->actions()->clear();

        uint32_t players_playing = 0;
        uint32_t spectators_count = spectators_.size();

        DEBUG("Expecting %d clients", size);
        for (uint32_t i = 0; i < size; ++i)
        {
            if (!msgr->poll(timeout_))
            {
                DEBUG("time out");
                break;
            }

            // Receive actions from one player
            DEBUG("recieving actions");
            msgr->recv_actions(&playerActions_);
            msgr->ack();

            if (playerActions_.all().empty())
            {
                DEBUG("actions() empty");
                uint32_t player_id = msgr->last_client_id();
                turn_players[player_id] = true;
                if (turn_players[player_id] != last_turn_players[player_id])
                {
                    DEBUG("client resurected");
                    playerActions_.clear();
                    i--;
                }
                else
                    players_playing++;
                continue;
            }

            // client sent no action, spectator sent ActionAck
            if (playerActions_.all().back()->id() == ACTION_ACK)
            {
                DEBUG("spectator obtained");
                spectators_count--;
            }
            else
            {
                uint32_t player_id = msgr->last_client_id();

                turn_players[player_id] = true;
                if (turn_players[player_id] != last_turn_players[player_id])
                {
                    DEBUG("client resurected");
                    // client resurected
                    playerActions_.clear();
                    i--;
                }
                else
                {
                    DEBUG("client obtained");
                    players_playing++;
                }
            }

            for (auto& playerAction : playerActions_.all())
                api_->actions()->add(std::move(playerAction));

            playerActions_.clear();
        }
        while (spectators_count > 0)
        {
            msgr->recv_actions(api_->actions());
            msgr->ack();
            spectators_count--;
        }

        last_turn_players = turn_players;
        for (unsigned i = 0; i < turn_players.size(); ++i)
            turn_players[i] = false;

        size = players_playing + spectators_.size();

        // Apply them onto the gamestate
        for (auto& action : api_->actions()->all())
        {
            api_->game_state_save();
            api_->game_state_apply(*action);
            actions.add(std::move(action));
        }

        // DEBUG("resolving %d", phase);
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
            for (uint32_t i = 0; i < players_.size(); ++i)
                api_->game_state().deactivateElfeVision(i);

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
}

void Rules::resolve_moves()
{
    DEBUG("resolve_moves");
    auto& pendingMoves = api_->game_state().getPendingMoves();

    for (auto unit : api_->game_state().getUnits())
        unit->resetPenombre();

    if (pendingMoves.size() == 0)
        return;

    for (auto& moves : pendingMoves)
    {
        for (auto& move : moves)
        {
            Unit_sptr unit =
                api_->game_state().getUnit(move.second->getPersoInfo());
            api_->game_state().getMap()->moveUnit(
                unit->getUnitInfo(), unit->getPosition(), move.first);
            unit->setPosition(move.first);
            unit->setOrientation(
                Map::getOrientation(move.first, unit->getPosition()));
        }
        for (auto unit : api_->game_state().getUnits())
            unit->addPenombre(api_->game_state().getMap()->getSurroundings(
                unit->getPosition(), unit->getOrientation(),
                unit->getVision()));
    }
    // It's kind of ugly but we're running out of time
    for (auto& move : pendingMoves[0])
        move.second->applyDirection(&api_->game_state());
    for (auto& moves : pendingMoves)
        moves.clear();
    pendingMoves.clear();
}

void Rules::resolve_attacks()
{
    DEBUG("resolve_attacks");
    auto& pendingAttacks = api_->game_state().getPendingAttacks();
    auto& pendingBastoooon = api_->game_state().getPendingBastoooon();
    std::map<int, int> markedUnits;

    DEBUG("attacks: %d", pendingAttacks.size());
    for (auto& attack : pendingAttacks)
    {
        if (attack->getType() != ATTAQUE_FUS_RO_DAH)
            break;
        DEBUG("FusRoDah");
        attack->markFusRoDah(&api_->game_state(), markedUnits);
    }
    for (auto& attack : pendingAttacks)
        attack->applyAttack(&api_->game_state());
    for (auto& attack : pendingBastoooon)
        api_->game_state().getUnit(attack->getPersoInfo())->saveLife();
    for (auto& attack : pendingBastoooon)
        attack->applyBastoooon(&api_->game_state());

    pendingAttacks.clear();
    pendingBastoooon.clear();
}

void Rules::resolve_points()
{
    DEBUG("resolve_points");
    GameState& st = api_->game_state();

    for (auto unit : st.getUnits())
    {
        if (!unit->isDead())
            continue;

        DEBUG("UNIT DEAD: player %d class %d", unit->getPlayer(),
              unit->getClasse());

        // Unit is dead
        unsigned int teamkill = 0;
        for (unit_info attacker : unit->getAttackers())
            if (attacker.player_id == unit->getPlayer())
                ++teamkill;

        // Only teamkill
        if (teamkill == unit->getAttackers().size())
        {
            DEBUG("teamkill");
            players_[unit->getPlayer()]->score -= 2;
        }
        // no teamkill, every team get a point
        else if (teamkill == 0)
        {
            std::set<int> attackers_team;
            for (unit_info attacker : unit->getAttackers())
            {
                attacker.debug();
                attackers_team.insert(attacker.player_id);
            }

            for (int team : attackers_team)
            {
                DEBUG("team: %d, score %d+1 from kill of team %d unit %d", team,
                      players_[team]->score, unit->getPlayer(),
                      unit->getClasse());
                players_[team]->score += 1;
            }
            players_[unit->getPlayer()]->score -= 1;
        }
        // else
        // mixed teamkill and offensive kill
        // no points given

        // Move unit to spawn position
        st.getMap()->moveUnit(unit->getUnitInfo(), unit->getPosition(),
                              unit->getSpawn());

        // reset life & cooldowns
        unit->respawn();
    }
}

void Rules::resolve_end_of_placement_turn()
{
    GameState& st = api_->game_state();
    Map* map = st.getMap();

    INFO("end of placement turn %d", st.getCurrentTurn());

    st.incrementTurn();

    if (st.getCurrentTurn() == map->getPlacementTurns())
    {
        INFO("end of placement phase");
        st.setPhase(PHASE_DEPLACEMENT);

        // End of placement phase
        // Save spawns
        for (auto unit : st.getUnits())
            unit->setSpawn(unit->getPosition());
    }
}

void Rules::resolve_end_of_deplacement_phase()
{
    GameState& st = api_->game_state();

    INFO("end of move phase %d", st.getCurrentTurn());

    st.setPhase(PHASE_ATTAQUE);
}

void Rules::resolve_end_of_attaque_phase()
{
    GameState& st = api_->game_state();

    INFO("end of attack phase %d", st.getCurrentTurn());

    st.incrementTurn();
    st.setPhase(PHASE_DEPLACEMENT);

    for (Unit_sptr unit : st.getUnits())
        unit->resetAttackers();
}

bool Rules::is_finished()
{
    return api_->game_state().isFinished();
}
