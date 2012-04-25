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

// /!\ Does not harm attacker
void BasicAttack::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=normale target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    // apply cooldown
    Ability::apply(st, attacker, target);

    UnitVect units = st->getMap()->getUnitsOn(target);

    for (auto unit : units)
    {
        if (unit == attacker)
            continue;

        st->getUnit(unit)->attacked(damages_, attacker);
    }
}

/*******************************************************************************
 * Voleur - Palantir
 */

erreur Palantir::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // check cooldown & valid position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    // TODO CHECK VISION

    return OK;
}

void Palantir::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=palantir target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    // apply cooldown
    Ability::apply(st, attacker, target);

    // set the palantir
    st->setPalantir(attacker.player_id, target);
}

/*
 * end - Voleur - Palantir
 ******************************************************************************/

/*******************************************************************************
 * Voleur - Traitrise
 */

erreur Traitrise::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // check cooldown & valid position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    // are target and attacker on the same cell?
    position pos = st.getUnit(attacker)->getPosition();
    if (pos != target)
        return POSITION_IMPOSSIBLE;

    return OK;
}

void Traitrise::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=traitrise target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    // apply cooldown
    Ability::apply(st, attacker, target);

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

/*
 * end - Voleur - Traitrise
 ******************************************************************************/

/*******************************************************************************
 * Barbare - Bastoooon
 */

erreur Bastoooon::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // check cooldown & valid position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    // In range?
    if (!st.getUnit(attacker)->isPositionInVision(st.getMap(), target))
        return POSITION_IMPOSSIBLE;

    return OK;
}

void Bastoooon::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=bastoooon target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    Map* map = st->getMap();

    // apply cooldown
    Ability::apply(st, attacker, target);

    position new_target;
    std::vector<std::pair<int, int>> cross = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    for (auto dxdy : cross)
    {
        new_target = position {target.x + dxdy.first, target.y + dxdy.second};

        if (map->isPositionValid(new_target))
        {
            UnitVect attacked_units = st->getMap()->getUnitsOn(new_target);
            for (unit_info attacked_unit: attacked_units)
                st->getUnit(attacked_unit)->attacked(BARBARE_ATTAQUE, attacker);
        }
    }
}

/*
 * end - Barbare - Bastoooon
 ******************************************************************************/

/*******************************************************************************
 * Barbare - FusRoDah
 */

erreur FusRoDah::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // check cooldown & valid position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    return OK;
}

void FusRoDah::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=fusrodah target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    // Map* map = st->getMap();

    // apply cooldown
    Ability::apply(st, attacker, target);

    // FIXME: jicks move the code here
}

/*
 * end - Barbare - FusRoDah
 ******************************************************************************/

/*******************************************************************************
 * Elfe - ElfeAttaque
 */

erreur ElfeAttaque::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // check cooldown & valid position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    // FIXME: halfr, vision

    return OK;
}

void ElfeAttaque::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=normale target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    // apply cooldown
    Ability::apply(st, attacker, target);

    UnitVect units = st->getMap()->getUnitsOn(target);

    for (auto unit : units)
    {
        if (unit == attacker)
            continue;

        st->getUnit(unit)->attacked(ELFE_ATTAQUE, attacker);
    }

}

/*
 * end - Elfe - ElfeAttaque
 ******************************************************************************/

/*******************************************************************************
 * Elfe - ISee
 */

erreur ISee::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // check cooldown & valid position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    return OK;
}

void ISee::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=isee target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    // Map* map = st->getMap();

    // apply cooldown
    Ability::apply(st, attacker, target);

    // FIXME: same shit as Palantir

}

/*
 * end - Elfe - ISee
 ******************************************************************************/

/*******************************************************************************
 * Elfe - Loto
 */

erreur Loto::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    // check cooldown & valid position
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    return OK;
}

void Loto::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=loto target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    // apply cooldown
    Ability::apply(st, attacker, target);

    UnitVect units = st->getMap()->getUnitsOn(target);

    for (auto unit : units)
    {
        if (unit == attacker)
            continue;

        st->getUnit(unit)->attacked(ELFE_ATTAQUE, attacker);
    }

}

/*
 * end - Elfe - Loto
 ******************************************************************************/
