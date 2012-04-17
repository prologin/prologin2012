#include <vector>

#include "map.hh"
#include "ability.hh"

int Ability::check(Map*, Unit*, Position) const
{
    if (cooldown_ > 0)
        return 1;
    return 0;
}

void Ability::apply(Map*, Unit*, Position)
{
    cooldown_ = cost_;
}

int BasicAttack::check(Map* map, Unit* attacker, Position target) const
{
    int err;

    err = Ability::check(map, attacker, target);
    if (err != 0)
        return err;

    // TODO
    return 0;
}

void BasicAttack::apply(Map* map, Unit* attacker, Position target)
{
    Ability::apply(map, attacker, target);

    std::vector<Unit*> units = map->getUnitsOn(target);

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        (*it)->attacked(damages_, attacker);
    }
}
