#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <cstdint>

# include "unit.hh"

// Class representing the player IA
class Player
{
public:
    Player()
        : points_(0), units_(3)
    {}

    Unit* getUnitVoleur();
    Unit* getUnitBarbare();
    Unit* getUnitElfe();

private:
    int16_t points_;
    std::vector< Unit > units_;
};

#endif // !PLAYER_HH_
