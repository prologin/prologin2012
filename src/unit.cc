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

int Unit::getMovementPoints() const
{
    return move_points_;
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

int Unit::getVision() const
{
    return vision_;
}

bool Unit::isPositionInVision(Map* map, position target) const
{
    // FIXME: jicks
    return false;
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

void Unit::resetAttackers()
{
    attackers_.clear();
}

// Return true if unit's life is less or equal to zero
bool Unit::isDead()
{
    return life_current_ <= 0;
}

Ability* Unit::getAbility(attaque_type id)
{
  CHECK((size_t)id < abilities_.size());

  return abilities_[id];
}

int Unit::getAbilityCooldown(attaque_type id) const
{
    return pickAbilityCooldown(id);
}

int Unit::pickAbilityCooldown(int ability_id) const
{
    CHECK((size_t)ability_id < abilities_.size());

    return abilities_[ability_id]->getCooldown();
}

void Unit::resetPenombre()
{
  penombre_.clear();
}

void Unit::addPenombre(std::vector<position> newPenombre)
{
  penombre_.insert(penombre_.end(), newPenombre.begin(), newPenombre.end());
}

std::vector<position> Unit::getPenombre() const
{
  return penombre_;
}

/******************************************************************************
 * Voleur
 **/

Voleur::Voleur(int player_id)
    : Unit(player_id, VOLEUR_DEPLACEMENT, VOLEUR_VISION, VOLEUR_VIE,
            PERSO_VOLEUR)
{
    abilities_.push_back(new BasicAttack(VOLEUR_ATTAQUE, VOLEUR_ATT_PORTEE));
    abilities_.push_back(new Traitrise());
}

Ability* Voleur::getAbility(attaque_type id)
{
     switch (id)
    {
    case ATTAQUE_NORMALE:
        return abilities_[0];
    case ATTAQUE_PALANTIR:
        return abilities_[1];
    case ATTAQUE_TRAITRISE:
        return abilities_[2];
    default:
        return 0;
    }
}

int Voleur::getAbilityCooldown(attaque_type id) const
{
    switch (id)
    {
    case ATTAQUE_NORMALE:
        return pickAbilityCooldown(0);
        break;
    case ATTAQUE_PALANTIR:
        return pickAbilityCooldown(1);
        break;
    case ATTAQUE_TRAITRISE:
        return pickAbilityCooldown(2);
        break;
    default:
        return -1;
    }
}

/******************************************************************************
 * Barbare
 **/

Barbare::Barbare(int player_id)
    : Unit(player_id, BARBARE_DEPLACEMENT, BARBARE_VISION, BARBARE_VIE,
            PERSO_BARBARE)
{
    abilities_.push_back(new BasicAttack(BARBARE_ATTAQUE, BARBARE_ATT_PORTEE));
}

Ability* Barbare::getAbility(attaque_type id)
{
     switch (id)
    {
    case ATTAQUE_NORMALE:
        return abilities_[0];
    case ATTAQUE_BASTOOOON:
        return abilities_[1];
    case ATTAQUE_FUS_RO_DAH:
        return abilities_[2];
    default:
        return 0;
    }
}

int Barbare::getAbilityCooldown(attaque_type id) const
{
    switch (id)
    {
    case ATTAQUE_NORMALE:
        return pickAbilityCooldown(0);
        break;
    case ATTAQUE_BASTOOOON:
        return pickAbilityCooldown(1);
        break;
    case ATTAQUE_FUS_RO_DAH:
        return pickAbilityCooldown(2);
        break;
    default:
        return -1;
    }
}

/******************************************************************************
 * Elfe
 **/

Elfe::Elfe(int player_id)
    : Unit(player_id, ELFE_DEPLACEMENT, ELFE_VISION, ELFE_VIE, PERSO_ELFE)
{
    abilities_.push_back(new BasicAttack(ELFE_ATTAQUE, ELFE_ATT_PORTEE));
}

Ability* Elfe::getAbility(attaque_type id)
{
     switch (id)
    {
    case ATTAQUE_NORMALE:
        return abilities_[0];
    case ATTAQUE_I_SEE:
        return abilities_[1];
    case ATTAQUE_LOTO:
        return abilities_[2];
    default:
        return 0;
    }
}

int Elfe::getAbilityCooldown(attaque_type id) const
{
    switch (id)
    {
    case ATTAQUE_NORMALE:
        return pickAbilityCooldown(0);
        break;
    case ATTAQUE_I_SEE:
        return pickAbilityCooldown(1);
        break;
    case ATTAQUE_LOTO:
        return pickAbilityCooldown(2);
        break;
    default:
        return -1;
    }
}
