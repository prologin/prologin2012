#ifndef ABILITY_HH_
# define ABILITY_HH_

# include <memory>
# include <list>

# include "constant.hh"

class Unit;

typedef std::shared_ptr<Unit> Unit_sptr;
typedef std::list<Unit_sptr> UnitList;

class Map;

class Ability
{
public:
    Ability(int cost)
        : cooldown_(0), cost_(cost)
    {};

    /*
     * check:
     *  - cooldown > 0
     *  - target is on the map
     */
    erreur check(Map* map, Unit_sptr attacker, position target) const;
    /*
     * apply:
     *  - add decrease life points
     */
    void apply(Map* map, Unit_sptr attacker, position target);

    int getCooldown() const;
    void resetCooldown();

private:
    // when ability is used, cooldown_ = cost
    int cooldown_;
    int cost_;
};

class BasicAttack : public Ability
{
public:
    BasicAttack(int damages, int range)
        : Ability(0), damages_(damages), range_(range)
    {};

    erreur check(Map* map, Unit_sptr attacker, position target) const;
    void apply(Map* map, Unit_sptr attacker, position target);

private:
    int damages_;
    int range_;
};

typedef std::shared_ptr<Ability> Ability_sptr;
typedef std::list<Ability_sptr> AbilityList;

#endif // !ABILITY_HH_
