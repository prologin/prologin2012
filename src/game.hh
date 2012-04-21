#ifndef GAME_HH_
# define GAME_HH_

# include <vector>

# include <rules/game-state.hh>
# include <rules/player.hh>

# include "unit.hh"

class Map;
class Player;

class GameState : public rules::GameState
{
public:
    GameState(Map* map, int player_count)
        : rules::GameState(), map_(map), player_count_(player_count),
        players_()
    {}

    GameState(const GameState& copy_from);

    virtual rules::GameState* copy() const;

    ~GameState();

    void init();

    void resolveMoves();
    void resolveAttacks();

    Map* getMap();
    size_t getPlayerCount();

private:
    Map* map_;
    int player_count_;
    rules::PlayerList players_;
    UnitList units_;
};

#endif // !GAME_HH_
