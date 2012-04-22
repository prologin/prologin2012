#include <utils/log.hh>

#include "unit.hh"
#include "ability.hh"
#include "constant.hh"

/*******************************************************************************
 * Unit
 */

unit_info Unit::getUnitInfo() const
{
    return unit_info { .player_id = player_id_, .classe = classe_};
}

int Unit::getPlayer() const
{
    return player_id_;
}

perso_classe Unit::getClasse() const
{
    return classe_;
}

int Unit::getCurrentLife() const
{
    return life_current_;
}

void Unit::resetLife()
{
    life_current_ = life_max_;
}

position Unit::getPosition() const
{
    return current_position_;
}

void Unit::setPosition(position p)
{
    current_position_ = p;
}

orientation Unit::getOrientation() const
{
    return orientation_;
}

void Unit::setOrientation(orientation direction)
{
    orientation_ = direction;
}

position Unit::getSpawn()
{
    return spawn_;
}

void Unit::setSpawn(position spawn)
{
    spawn_ = spawn;
}

void Unit::respawn()
{
    for (auto it = abilities_.begin(); it != abilities_.end(); ++it)
        (*it)->resetCooldown();

    resetLife();
    current_position_ = getSpawn();
}

int Unit::getAbilityCooldown(int ability_id) const
{
    CHECK((size_t)ability_id < abilities_.size());

    return abilities_[ability_id]->getCooldown();
}

void Unit::attacked(int damages, unit_info attacker)
{
    life_current_ -= damages;
    attackers_.push_back(attacker);
}

UnitVect Unit::getAttackers() const
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
 **/

Voleur::Voleur(int player_id)
    : Unit(player_id, VOLEUR_DEPLACEMENT, PERSO_VOLEUR)
{
    abilities_.push_back(new BasicAttack(VOLEUR_ATTAQUE, VOLEUR_ATT_PORTEE));
}

/******************************************************************************
 * Barbare
 **/

Barbare::Barbare(int player_id)
    : Unit(player_id, BARBARE_DEPLACEMENT, PERSO_BARBARE)
{
    abilities_.push_back(new BasicAttack(BARBARE_ATTAQUE, BARBARE_ATT_PORTEE));
}

/******************************************************************************
 * Elfe
 **/

Elfe::Elfe(int player_id)
    : Unit(player_id, ELFE_DEPLACEMENT, PERSO_ELFE)
{
    abilities_.push_back(new BasicAttack(ELFE_ATTAQUE, ELFE_ATT_PORTEE));
}
