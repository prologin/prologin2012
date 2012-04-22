#include <vector>

#include "map.hh"
#include "game.hh"
#include "ability.hh"
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

    // TODO check vision
    return OK;
}

void BasicAttack::apply(GameState* st, unit_info attacker, position target)
{
    Ability::apply(st, attacker, target);

    UnitVect units = st->getMap()->getUnitsOn(target);

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        st->getUnit(*it)->attacked(damages_, attacker);
    }
}

/*******************************************************************************
 * Voleur - OneShot
 */

erreur OneShot::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // Check cooldown & position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    // Target and attacker are on the same cell?
    position pos = st.getUnit(attacker)->getPosition();
    if (pos != target)
        return POSITION_IMPOSSIBLE;

    return OK;
}
