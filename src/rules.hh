#ifndef RULES_HH_
# define RULES_HH_

# include <utils/dll.hh>
# include <rules/options.hh>
# include <net/client-messenger.hh>
# include <net/server-messenger.hh>

# include "api.hh"

# define PHASE_PLACEMENT 0
# define PHASE_DEPLACEMENT 1
# define PHASE_ATTACKE 2

typedef void (*f_champion_partie_init)();
typedef void (*f_champion_jouer_placement)();
typedef void (*f_champion_jouer_deplacement)();
typedef void (*f_champion_jouer_attaque)();
typedef void (*f_champion_partie_fin)();

class Rules
{
public:
    explicit Rules(const rules::Options& opt);
    virtual ~Rules();

    void client_loop(net::ClientMessenger_sptr msgr);
    void server_loop(net::ServerMessenger_sptr msgr);

protected:
    int is_finished();

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
    rules::PlayerVector_sptr players_;

    int winner_;
};

#endif // !RULES_HH_
