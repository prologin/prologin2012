#ifndef UNIT_HH_
# define UNIT_HH_

# include <vector>
# include <cstdint>

# include "position.hh"
# include "ability.hh"

class Unit
{
public:
    Unit(uint8_t player_id)
        : abilities_(), player_id_(player_id), spawn_(Position(0, 0)),
        life_max_(10), life_current_(10), attackers_()
    {}

    uint8_t getCurrentLife() const;
    void resetLife();

    Position getSpawn();
    void setSpawn(Position p);
    /**
     * reset cooldown on all abilities
     * reset life
     * does not move unit
     */
    void respawn();

    void useAbility(uint8_t ability_id, Map* map, Position* target);
    uint8_t getAbilityCooldown(uint8_t ability_id);

    /**
     * reduce life
     * add attacker to attackers list
     */
    void attacked(uint8_t damages, Unit* attacker);
    std::vector<Unit*> getAttackers() const;
    bool isDead();

protected:
    std::vector<Ability*> abilities_;

private:
    uint8_t player_id_;

    Position spawn_;

    uint8_t life_max_;
    uint8_t life_current_;

    std::vector<Unit*> attackers_;

    orientation orientation_;
};

class Voleur : public Unit
{
    Voleur(uint8_t player_id);
    ~Voleur();
};
#endif // !UNIT_HH_
