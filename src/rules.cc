#include "rules.hh"

#include <utils/log.hh>
#include <utils/buffer.hh>

#include "action-move.hh"
#include "action-attack.hh"
#include "game.hh"
#include "map.hh"

Rules::Rules(const rules::Options& opt)
    : opt_(opt),
      champion_(nullptr)
{

    Map* map;
    map->load(opt.map);
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
        champion_partie_fin = champion_-><f_champion_partie_fin>("partie_fin");

        champion_init();
    }

    players_ = opt.players;

    // Register Actions
    api_->actions()->register_action(ACTION_MOVE,
            []() -> rules::IAction* { return new ActionMove(); });
    api_->actions()->register_action(ACTION_ATTACK,
            []() -> rules::IAction* { return new ActionAttack(); });
}

rules::~rules()
{
    if (champion_)
    {
        champion_end();
        delete champion_;
    }

    delete api_;
}

void Rules::client_loop()
{
    CHECK(champion_ != nullptr);

    while ((winner_ = is_finished()) == -1)
    {
        DEBUG("NEW TURN");

        api_->actions()->clear();

        // Play
        champion_play();

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

        if (game_phase == PHASE_PLACEMENT || PHASE_DEPLACEMENT)
            api_->game_state().resolveMoves();

        if (game_phase == PHASE_ATTACK)
            api_->game_state().resolveAttacks();

        // XXX: debug
        //std::cout << *api_->game_state();
    }

    DEBUG("winner = %i", winner_);
}

void Rules::server_loop(net::ServerMessenger_sptr msgr)
{
    rules::Actions actions;

    while ((winner_ = is_finished()) == -1)
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
                actions.add_action(action);
            }

            msgr->ack();
        }

        if (game_phase == PHASE_PLACEMENT || PHASE_DEPLACEMENT)
            api_->game_state().resolveMoves();

        if (game_phase == PHASE_ATTACK)
            api_->game_state().resolveAttacks();

        // Send actions
        utils::Buffer send_buf;

        actions.handle_buffer(send_buf);

        msgr->push(send_buf);

        // XXX: debug
        //std::cout << *api_->game_state();
    }

    DEBUG("winner = %i", winner_);
}
