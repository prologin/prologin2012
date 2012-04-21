#ifndef ABILITY_HH_
# define ABILITY_HH_

# include <memory>
# include <list>

# include "constant.hh"

class Map;
class Unit;

class Ability
{
public:
    Ability(uint8_t cost)
        : cooldown_(0), cost_(cost)
    {};

    /*
     * check:
     *  - cooldown > 0
     *  - target is on the map
     */
    erreur check(Map* map, Unit* attacker, position target) const;
    void apply(Map* map, Unit* attacker, position target);

    uint8_t getCooldown() const;
    void resetCooldown();

private:
    // when ability is used, cooldown_ = cost
    uint8_t cooldown_;
    uint8_t cost_;
};

class BasicAttack : public Ability
{
public:
    BasicAttack(uint8_t damages, uint8_t range)
        : Ability(0), damages_(damages), range_(range)
    {};

    erreur check(Map* map, Unit* attacker, position target) const;
    void apply(Map* map, Unit* attacker, position target);

private:
    uint8_t damages_;
    uint8_t range_;
};

typedef std::shared_ptr<Ability> Ability_sptr;
typedef std::list<Ability_sptr> AbilityList;

#endif // !ABILITY_HH_
