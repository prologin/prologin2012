#ifndef ABILITY_HH_
# define ABILITY_HH_

# include <memory>
# include <list>

# include "constant.hh"

struct unit_info;

class GameState;

class Unit;

typedef std::shared_ptr<Unit> Unit_sptr;
typedef std::vector<Unit_sptr> UnitList;

class Map;

class Ability
{
public:
    Ability(int cost)
        : cooldown_(0), cost_(cost)
    {};

    /* check:
     *  - cooldown > 0
     *  - target is on the map
     */
    erreur check(const GameState& st, unit_info attacker, position target)
        const;

    /* apply:
     *  - add decrease life points
     */
    void apply(GameState* st, unit_info attacker, position target);

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

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);

private:
    int damages_;
    int range_;
};

class OneShot : public Ability
{
public:
    OneShot(int cost)
        : Ability(cost)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

#endif // !ABILITY_HH_
