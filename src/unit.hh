#ifndef UNIT_HH_
# define UNIT_HH_

# include <vector>
# include <list>
# include <cstdint>
# include <memory>

# include "ability.hh"
# include "constant.hh"

class Unit;

typedef std::shared_ptr<Unit> Unit_sptr;
typedef std::list<Unit_sptr> UnitList;

class Unit
{
public:
    Unit(int player_id, int move_points, perso_classe classe)
        : abilities_(), player_id_(player_id), classe_(classe),
        spawn_(position {0, 0}), life_max_(10), life_current_(10),
        move_points_(move_points), attackers_()
    {}

    Unit(int player_id, int move_points)
        : Unit(player_id, move_points, PERSO_VOLEUR)
    {}

    int getPlayer() const;
    perso_classe getClasse() const;

    int getCurrentLife() const;
    void resetLife();

    orientation getOrientation() const;
    void setOrientation(orientation direction);

    position getSpawn();
    void setSpawn(position p);
    /**
     * reset cooldown on all abilities
     * reset life
     * does not move unit
     */
    void respawn();

    void useAbility(int ability_id, Map* map, position* target);
    int getAbilityCooldown(int ability_id);

    /**
     * reduce life
     * add attacker to attackers list
     */
    void attacked(int damages, Unit_sptr attacker);
    UnitList getAttackers() const;
    bool isDead();

protected:
    AbilityList abilities_;

private:
    int player_id_;
    perso_classe classe_;

    position spawn_;

    int life_max_;
    int life_current_;

    int move_points_;

    UnitList attackers_;

    orientation orientation_;
};

class Voleur : public Unit
{
public:
    Voleur(int player_id);
};

class Barbare : public Unit
{
public:
    Barbare(int player_id);
};

class Elfe : public Unit
{
public:
    Elfe(int player_id);
};

#endif // !UNIT_HH_
