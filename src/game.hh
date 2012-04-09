#ifndef PROLOGIN2012_GAME_HH_
# define PROLOGIN2012_GAME_HH_

# include <cstdint>
# include <string>

# include "map.hh"

class Game
{
public:
    Game(uint32_t nb_players, const std::string& map);

    uint32_t nb_players()
        { return nb_players_; }
    Map& map()
        { return map_; }
    const Map& map() const
        { return map_; }

private:
    uint32_t nb_players_;
    Map map_;
};

#endif // PROLOGIN2012_GAME_HH_
