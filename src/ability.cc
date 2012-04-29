#include <vector>
#include <cstdlib>
#include <algorithm>

#include "ability.hh"

#include "map.hh"
#include "cell.hh"
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

void Ability::decrementCooldown()
{
    cooldown_ = (cooldown_ > 0) ? cooldown_ - 1 : 0;
}

void Ability::resetCooldown()
{
    cooldown_ = 0;
}

/*******************************************************************************
 * Voleur - VoleurAttaque
 */

erreur VoleurAttaque::check(const GameState& st, unit_info attacker,
        position target) const
{
    erreur err;
    if ((err = Ability::check(st, attacker, target)) != OK)
        return err;

    Unit_sptr unit = st.getUnit(attacker);

    unit->setVision(1);

    // check range
    if (!unit->isPositionInVision(st.getMap(), target))
    {
        unit->setVision(VOLEUR_VISION);
        return POSITION_IMPOSSIBLE;
    }

    unit->setVision(VOLEUR_VISION);

    return OK;
}

// /!\ Does not harm attacker
void VoleurAttaque::apply(GameState* st, unit_info attacker, position target)
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

        st->getUnit(unit)->attacked(VOLEUR_ATTAQUE, attacker);
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

    if (!st.getUnit(attacker)->isPositionInVision(st.getMap(), target))
      return POSITION_IMPOSSIBLE;

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
    for (unit_info attacked_unit : attacked_units)
    {
        // same unit or same team, skip
        if (attacked_unit == attacker
                || attacked_unit.player_id == attacker.player_id)
        {
            DEBUG("dropping");
            attacked_unit.debug();
            continue;
        }

        // 255 dmg should be enough to kill him
        st->getUnit(attacked_unit)->attacked(255, attacker);
    }
}

/*
 * end - Voleur - Traitrise
 ******************************************************************************/

/*******************************************************************************
 * Barbare - BarbareAttaque
 */

erreur BarbareAttaque::check(const GameState& st, unit_info attacker,
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

void BarbareAttaque::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=normale target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    Map* map = st->getMap();

    // apply cooldown
    Ability::apply(st, attacker, target);

    position new_target;
    std::vector<position> cross = {{-1, 0}, {1, 0}, {0, 0}, {0, 1}, {0, -1}};
    for (auto dxdy : cross)
    {
        new_target = position {target.x + dxdy.x, target.y + dxdy.y};

        if (map->isPositionValid(new_target))
        {
            UnitVect attacked_units = st->getMap()->getUnitsOn(new_target);
            for (unit_info attacked_unit: attacked_units)
                st->getUnit(attacked_unit)->attacked(BARBARE_ATTAQUE, attacker);
        }
    }
}

/*
 * end - Barbare - BarbareAttaque
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

    Unit_sptr unit = st.getUnit(attacker);

    unit->setVision(BARBARE_BASTOOOON_PORTEE);

    // check range
    if (!unit->isPositionInVision(st.getMap(), target))
    {
        unit->setVision(BARBARE_VISION);
        return POSITION_IMPOSSIBLE;
    }

    unit->setVision(BARBARE_VISION);

    return OK;
}

void Bastoooon::apply(GameState* st, unit_info attacker, position target)
{
    INFO("player_id=%d unit=%d attack=bastoooon target=(%d, %d)",
            attacker.player_id, attacker.classe, target.x, target.y);

    Map* map = st->getMap();

    // apply cooldown
    Ability::apply(st, attacker, target);

    // ok :)
    int damages = BARBARE_VIE - st->getUnit(attacker)->getCurrentLife() + 1;

    position new_target;
    std::vector<position> cross = {{-1, 0}, {1, 0}, {0, 0}, {0, 1}, {0, -1}};
    for (auto dxdy : cross)
    {
        new_target = position {target.x + dxdy.x, target.y + dxdy.y};

        if (map->isPositionValid(new_target))
        {
            UnitVect attacked_units = st->getMap()->getUnitsOn(new_target);
            for (unit_info attacked_unit: attacked_units)
            {
                if (attacked_unit == attacker) continue;
                st->getUnit(attacked_unit)->attacked(damages, attacker);
            }
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

    // apply cooldown
    Ability::apply(st, attacker, target);

    Map* map = st->getMap();
    Unit_sptr attackerUnit = st->getUnit(attacker);
    position attackerPosition = attackerUnit->getPosition();
    orientation direction = attackerUnit->getOrientation();
    int vision = attackerUnit->getVision();
    int South = (direction == ORIENTATION_SUD) - (direction == ORIENTATION_NORD);
    int East = (direction == ORIENTATION_EST) - (direction == ORIENTATION_OUEST);

    auto unitsPositions = map->getSurroundings(attackerPosition, direction, vision);
    for (auto unitsPosition : unitsPositions)
    {
        int maxDistance = vision - abs((unitsPosition.x - attackerPosition.x) * East)
            + abs((unitsPosition.y - attackerPosition.y) * South) + 1;

        // We calculate how much we can push the units on the cell
        position newPosition = unitsPosition;
        for (int i = 0; i < maxDistance; ++i)
        {
            newPosition = { newPosition.x + East, newPosition.y + South };
            if (map->isPositionValid(newPosition) &&
                    map->getCell(newPosition)->getType() != ZONE_MUR)
                continue;
            newPosition = { newPosition.x - East, newPosition.y - South };
            break;
        }

        // We move the units
        position displacement = { (newPosition.x - unitsPosition.x) * East,
                                  (newPosition.y - unitsPosition.y) * South};
        for (auto unitInfo : map->getCell(unitsPosition)->getUnits())
        {
            if (unitInfo == attacker) continue;
            st->getUnit(unitInfo)->setDisplacement(displacement);
            st->getUnit(unitInfo)->setPosition(newPosition);
            map->moveUnit(unitInfo, unitsPosition, newPosition);
        }
    }
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

    Map* map = st.getMap();

    for (Unit_sptr unit : st.getUnits())
        if (unit->getPlayer() == attacker.player_id && 
                unit->isPositionInVision(map, target))
            return OK;

    if (st.isPalantirActivated(attacker.player_id))
    {
        position palantir = st.getPalantir(attacker.player_id);

        auto square = map->getSquareVision(palantir, VOLEUR_VISION);
        if (std::find(square.begin(), square.end(), target) != square.end())
            return OK;
    }

    if (st.isElfeVisionActivated(attacker.player_id))
    {
        position elfe_vision = st.getElfeVision(attacker.player_id);

        auto square = map->getSquareVision(elfe_vision, ELFE_VISION);
        if (std::find(square.begin(), square.end(), target) != square.end())
            return OK;
    }

    return POSITION_IMPOSSIBLE;
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

    // apply cooldown
    Ability::apply(st, attacker, target);

    st->setElfeVision(attacker.player_id, target);
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
        st->getUnit(unit)->attacked(ELFE_ATTAQUE * 2, attacker);
}

/*
 * end - Elfe - Loto
 ******************************************************************************/
