#include "unit.hh"

uint8_t Unit::getCurrentLife() const
{
    return life_current_;
}

void Unit::resetLife()
{
    life_current_ = life_max_;
}

Position Unit::getSpawn()
{
    return spawn_;
}

void Unit::setSpawn(Position spawn)
{
    spawn_ = spawn;
}

void Unit::respawn()
{
    for (auto it = abilities_.begin(); it != abilities_.end(); ++it)
        (*it)->resetCooldown();
    
    resetLife();
}

void Unit::attacked(uint8_t damages, Unit* attacker)
{
    life_current_ -= damages;
    attackers_.push_back(attacker);
}

std::vector<Unit*> Unit::getAttackers() const
{
    return attackers_;
}

// Return true if unit's life is less or equal to zero
bool Unit::isDead()
{
    return life_current_ <= 0;
}


/******************************************************************************
 * Voleur
 * */

Voleur::Voleur(uint8_t player_id)
    : Unit(player_id)
{
    abilities_.push_back(new BasicAttack(3, 1));
}
