#include <vector>

#include "map.hh"
#include "ability.hh"


erreur Ability::check(Map* map, Unit*, position p) const
{
    if (cooldown_ > 0)
        return ATTAQUE_INDISPONIBLE;
    if (!map->isPositionValid(p))
        return POSITION_IMPOSSIBLE;
    return OK;
}

void Ability::apply(Map*, Unit*, position)
{
    cooldown_ = cost_;
}

uint8_t Ability::getCooldown() const
{
    return cooldown_;
}

void Ability::resetCooldown()
{
    cooldown_ = 0;
}

erreur BasicAttack::check(Map* map, Unit* attacker, position target) const
{
    erreur err;
    if ((err = Ability::check(map, attacker, target)) != OK)
        return err;

    // TODO
    return OK;
}

void BasicAttack::apply(Map* map, Unit* attacker, position target)
{
    Ability::apply(map, attacker, target);

    std::vector<Unit*> units = map->getUnitsOn(target);

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        (*it)->attacked(damages_, attacker);
    }
}
