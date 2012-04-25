#ifndef UNIT_HH_
# define UNIT_HH_

# include <vector>
# include <list>
# include <cstdint>
# include <memory>

# include "constant.hh"
# include "safety.hh"

class Map;

/*******************************************************************************
 * unit_info
 */

// Used as a basic descriptor for an unit, easily copyable, used to refer to an
// Unit in a Cell
typedef struct unit_info
{
    int player_id;
    perso_classe classe;
} unit_info;

typedef std::vector<unit_info> UnitVect;

inline bool operator==(const unit_info& a, const unit_info& b)
{
    return a.player_id == b.player_id && a.classe == b.classe;
}

inline bool operator!=(const unit_info& a, const unit_info& b)
{
    return !(a == b);
}

/*******************************************************************************
 * Unit
 */

class Ability;

class Unit
{
public:
    Unit(int player_id, int move_points, int vision, int life,
            perso_classe classe)
        : abilities_(),
          player_id_(player_id),
          classe_(classe),
          vision_(vision),
          life_max_(life),
          life_current_(life),
          spawn_(position {0, 0}),
          current_position_(position {0, 0}),
          move_points_(move_points),
          attackers_(),
          orientation_(ORIENTATION_NORD),
          penombre_()
    {}

    // by default, for test purposes only, creata a Voleur
    Unit(int player_id, int move_points)
        : Unit(player_id, move_points, VOLEUR_VISION, VOLEUR_VIE, PERSO_VOLEUR)
    {}

    unit_info getUnitInfo() const;

    int getPlayer() const;
    perso_classe getClasse() const;

    int getCurrentLife() const;
    void resetLife();

    position getPosition() const;
    void setPosition(position p);

    int getMovementPoints() const;

    orientation getOrientation() const;
    void setOrientation(orientation direction);

    position getSpawn();
    void setSpawn(position p);
    /**
     * reset cooldown on all abilities
     * reset life
     * reset its position but does not move the unit on the map TODO
     */
    void respawn();

    int getVision() const;
    bool isPositionInVision(Map* map, position target) const;

    /**
     * reduce life
     * add attacker to attackers list
     */
    void attacked(int damages, unit_info attacker);
    UnitVect getAttackers() const;
    void resetAttackers();

    bool isDead();

    virtual Ability* getAbility(attaque_type id);
    virtual int getAbilityCooldown(attaque_type id) const;

    void resetPenombre();
    void addPenombre(std::vector<position> newPenombre);
    std::vector<position> getPenombre() const;

protected:
    int pickAbilityCooldown(int ability_id) const;

protected:
    std::vector<Ability*> abilities_;

private:
    int player_id_;
    perso_classe classe_;
    int vision_;

    int life_max_;
    int life_current_;

    position spawn_;
    position current_position_;

    int move_points_;

    UnitVect attackers_;

    orientation orientation_;

    std::vector<position> penombre_;
};

typedef std::shared_ptr<Unit> Unit_sptr;
typedef std::vector<Unit_sptr> Units;


/*******************************************************************************
 * Voleur
 */

class Voleur : public Unit
{
public:
    Voleur(int player_id);

    virtual Ability* getAbility(attaque_type id);
    virtual int getAbilityCooldown(attaque_type id) const;
};

/*******************************************************************************
 * Barbare
 */

class Barbare : public Unit
{
public:
    Barbare(int player_id);

    virtual Ability* getAbility(attaque_type id);
    virtual int getAbilityCooldown(attaque_type id) const;
};

/*******************************************************************************
 * Elfe
 */

class Elfe : public Unit
{
public:
    Elfe(int player_id);

    virtual Ability* getAbility(attaque_type id);
    virtual int getAbilityCooldown(attaque_type id) const;
};

#endif // !UNIT_HH_
