#ifndef RULES_HH_
# define RULES_HH_

# include <utils/dll.hh>
# include <utils/sandbox.hh>
# include <rules/options.hh>
# include <rules/client-messenger.hh>
# include <rules/server-messenger.hh>
# include <rules/player.hh>

# include "api.hh"

typedef void (*f_champion_partie_init)();
typedef void (*f_champion_jouer_placement)();
typedef void (*f_champion_jouer_deplacement)();
typedef void (*f_champion_jouer_attaque)();
typedef void (*f_champion_partie_fin)();

class Rules
{
public:
    explicit Rules(const rules::Options& opt);
    Rules(rules::Players_sptr players, Api* api);

    virtual ~Rules();

    void client_loop(rules::ClientMessenger_sptr msgr);
    void spectator_loop(rules::ClientMessenger_sptr msgr);
    void server_loop(rules::ServerMessenger_sptr msgr);

    void resolve_moves();
    void resolve_attacks();
    void resolve_points();
    void resolve_end_of_placement_turn();
    void resolve_end_of_deplacement_phase();
    void resolve_end_of_attaque_phase();

protected:
    bool is_finished();

protected:
    f_champion_partie_init champion_partie_init;
    f_champion_jouer_placement champion_jouer_placement;
    f_champion_jouer_deplacement champion_jouer_deplacement;
    f_champion_jouer_attaque champion_jouer_attaque;
    f_champion_partie_fin champion_partie_fin;

private:
    rules::Options opt_;
    utils::DLL* champion_;
    Api* api_;
    rules::Players_sptr players_;
    rules::Players_sptr spectators_;

    int timeout_;
    int winner_;

    utils::Sandbox sandbox_;
};

#endif // !RULES_HH_
