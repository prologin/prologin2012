#ifndef UNIT_HH_
# define UNIT_HH_

# include <vector>
# include <list>
# include <cstdint>
# include <memory>

# include "ability.hh"
# include "constant.hh"

class Unit
{
public:
    Unit(uint8_t player_id, uint8_t move_points)
        : abilities_(), player_id_(player_id), spawn_(position {0, 0}),
        life_max_(10), life_current_(10), move_points_(move_points),
        attackers_()
    {}

    uint8_t getCurrentLife() const;
    void resetLife();

    position getSpawn();
    void setSpawn(position p);
    /**
     * reset cooldown on all abilities
     * reset life
     * does not move unit
     */
    void respawn();

    void useAbility(uint8_t ability_id, Map* map, position* target);
    uint8_t getAbilityCooldown(uint8_t ability_id);

    /**
     * reduce life
     * add attacker to attackers list
     */
    void attacked(uint8_t damages, Unit* attacker);
    std::vector<Unit*> getAttackers() const;
    bool isDead();

protected:
    AbilityList abilities_;

private:
    uint8_t player_id_;

    position spawn_;

    uint8_t life_max_;
    uint8_t life_current_;

    uint8_t move_points_;

    std::vector<Unit*> attackers_;

    orientation orientation_;
};

class Voleur : public Unit
{
public:
    Voleur(uint8_t player_id);
};

class Barbare : public Unit
{
public:
    Barbare(uint8_t player_id);
};

class Elfe : public Unit
{
public:
    Elfe(uint8_t player_id);
};

typedef std::shared_ptr<Unit> Unit_sptr;
typedef std::list<Unit_sptr> UnitList;

#endif // !UNIT_HH_
