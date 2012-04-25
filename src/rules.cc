#include <fstream>
#include <map>

#include "rules.hh"

#include <utils/log.hh>
#include <utils/buffer.hh>

#include "constant.hh"
#include "action-move.hh"
#include "action-attack.hh"
#include "game.hh"
#include "map.hh"

Rules::Rules(const rules::Options& opt)
    : opt_(opt),
      champion_(nullptr),
      game_phase_(PHASE_PLACEMENT),
      sandbox_()
{
    // Load map from file
    std::ifstream ifs(opt.map_name);

    Map* map = new Map();
    map->load(ifs);

    GameState* game_state = new GameState(map, opt.players);

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

        champion_partie_init();
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
      game_phase_(PHASE_PLACEMENT),
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
        champion_partie_fin();
        delete champion_;
    }

    delete api_;
}

void Rules::client_loop(rules::ClientMessenger_sptr msgr)
{
    CHECK(champion_ != nullptr);

    while (!is_finished())
    {
        DEBUG("NEW TURN");

        api_->actions()->clear();

        switch (game_phase_)
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

        // Send actions
        utils::Buffer send_buf;

        api_->actions()->handle_buffer(send_buf);

        msgr->send(send_buf);
        msgr->wait_for_ack();

        api_->actions()->clear();

        for (uint32_t i = 0; i < players_->players.size(); ++i)
        {
            // Receive actions
            utils::Buffer* pull_buf = msgr->pull();

            // Put them in the API container
            api_->actions()->handle_buffer(*pull_buf);

            delete pull_buf;

            // Apply them onto the gamestate
            for (auto& action : api_->actions()->actions())
            {
                api_->game_state_set(action->apply(api_->game_state()));
            }
        }

        switch (game_phase_)
        {
        case PHASE_DEPLACEMENT:
        case PHASE_PLACEMENT:
            resolve_moves();
            break;
        case PHASE_ATTAQUE:
            resolve_attacks();
            resolve_points();
            break;
        }
    }

    DEBUG("winner = %i", winner_);
}

void Rules::server_loop(rules::ServerMessenger_sptr msgr)
{
    CHECK(champion_ == nullptr);

    rules::Actions actions;

    while (!is_finished())
    {
        DEBUG("NEW TURN");

        api_->actions()->clear();

        for (uint32_t i = 0; i < players_->players.size(); ++i)
        {
            // Receive actions
            utils::Buffer* pull_buf = msgr->recv();

            // Put them in the API container
            api_->actions()->handle_buffer(*pull_buf);

            delete pull_buf;

            // Apply them onto the gamestate
            for (auto& action : api_->actions()->actions())
            {
                api_->game_state_set(action->apply(api_->game_state()));
                actions.add(action);
            }

            msgr->ack();
        }

        // Send actions
        utils::Buffer send_buf;

        actions.handle_buffer(send_buf);

        msgr->push(send_buf);
    }

    DEBUG("winner = %i", winner_);
}

void Rules::resolve_moves()
{
    auto& pendingMoves = api_->game_state()->getPendingMoves();

    for (auto unit : api_->game_state()->getUnits())
        unit->resetPenombre();
    for (auto& moves : pendingMoves)
    {
        for (auto& move : moves)
        {
            move.second->setPosition(move.first);
            api_->game_state()->getMap()->moveUnit(move.second->getUnitInfo(),
                        move.second->getPosition(), move.first);
            move.second->setOrientation(Map::getOrientation(move.first,
                        move.second->getPosition()));
        }
        for (auto unit : api_->game_state()->getUnits())
            unit->addPenombre(
                    api_->game_state()->getMap()->getSurroundings(
                        unit->getPosition(),
                        unit->getOrientation(), unit->getVision()));
        moves.clear();
    }
    pendingMoves.clear();
}

void Rules::resolve_attacks()
{
    auto pendingAttacks = api_->game_state()->getPendingAttacks();
    std::map<int, int> markedUnits;

    for (auto attack : pendingAttacks)
    {
        if (attack->getType() != ATTAQUE_FUS_RO_DAH)
            break;
        attack->markFusRohDah(api_->game_state(), markedUnits);
    }
    for (auto attack : pendingAttacks)
        attack->applyAttack(api_->game_state());

    pendingAttacks.clear();
}

void Rules::resolve_points()
{
    // FIXME halfr
}

void Rules::resolve_end_of_turn()
{
    // FIXME halfr
    api_->game_state()->incrementTurn();
}

bool Rules::is_finished()
{
    return api_->game_state()->isFinished();
}
