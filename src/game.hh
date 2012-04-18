#ifndef GAME_HH_
# define GAME_HH_

# include <vector>

class Map;

class Game
{
public:
    Game(Map* map)
        : map_(map), players_()
    {}

    void resolveMoves();
    void resolveAttacks();

    ~Game();

private:
    Map* map_;
    std::vector<Player*> players_;
}

#endif // !GAME_HH_
