#include <cstdint>

#include "player.hh"

int16_t Player::getPoints()
{
    return points_;
}

Unit* Player::getUnitVoleur()
{
    return units_[0];
}

Unit* Player::getUnitBarbare()
{
    return units_[1];
}

Unit* Player::getUnitElfe()
{
    return units_[2];
}
