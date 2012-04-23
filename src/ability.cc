#include <vector>
#include <cstdlib>

#include "ability.hh"

#include "map.hh"
#include "game.hh"
#include "unit.hh"

/*******************************************************************************
 * Ability
 */

erreur Ability::check(const GameState& st, unit_info, position target) const
{
    if (cooldown_ > 0)
        return ATTAQUE_INDISPONIBLE;
    if (!st.getMap()->isPositionValid(target))
        return POSITION_IMPOSSIBLE;
    return OK;
}

void Ability::apply(GameState*, unit_info, position)
{
    cooldown_ = cost_;
}

int Ability::getCooldown() const
{
    return cooldown_;
}

void Ability::resetCooldown()
{
    cooldown_ = 0;
}

/*******************************************************************************
 * BasicAttack
 */

erreur BasicAttack::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    position  attacker_pos = st.getUnit(attacker)->getPosition();

    // check range
    if (abs(target.x - attacker_pos.x)
            + abs(target.y - attacker_pos.y) > range_)
        return POSITION_IMPOSSIBLE;

    return OK;
}

void BasicAttack::apply(GameState* st, unit_info attacker, position target)
{
    Ability::apply(st, attacker, target);

    UnitVect units = st->getMap()->getUnitsOn(target);

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        if (*it == attacker)
            continue;

        st->getUnit(*it)->attacked(damages_, attacker);
    }
}

/*******************************************************************************
 * Voleur - Traitrise
 */

erreur Traitrise::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // Check cooldown & position valid
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    // Are target and attacker on the same cell?
    position pos = st.getUnit(attacker)->getPosition();
    if (pos != target)
        return POSITION_IMPOSSIBLE;

    return OK;
}

void apply(GameState* st, unit_info attacker, position target)
{
    UnitVect attacked_units = st->getMap()->getUnitsOn(target);
    for (auto it = attacked_units.begin(); it != attacked_units.end(); ++it)
    {
        unit_info attacked_unit = *it;
        // TODO TEST
        // same unit or same team, skip
        if (attacked_unit == attacker
                || attacked_unit.player_id == attacker.player_id)
            continue;

        // 255 dmg should be enough to kill him
        st->getUnit(attacked_unit)->attacked(255, attacker);
    }
}
