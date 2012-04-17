#include "unit.hh"

Unit::Unit(Position p)
    : abilities_(), spawn_(p), current_position_(p), life_max_(10),
    life_current_(10), attackers_()
{}

Position Unit::getSpawn()
{
    return spawn_;
}

void Unit::setSpawn(Position spawn)
{
    spawn_ = spawn;
}

void Unit::attacked(uint8_t damages, Unit* attacker)
{
    life_current_ -= damages;
    attackers_.push_back(attacker);
}

// Return true if unit's life is less or equal to zero
bool Unit::isDead()
{
    return life_current_ <= 0;
}


/******************************************************************************
 * Voleur
 * */

Voleur::Voleur(Position p)
    : Unit(p)
{
    abilities_.push_back(new BasicAttack(3, 1));
}
