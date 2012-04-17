#ifndef UNIT_HH_
# define UNIT_HH_

# include <vector>
# include <cstdint>

# include "position.hh"
# include "ability.hh"

class Unit
{
public:
    Unit(Position p);

    Position getSpawn();
    void setSpawn(Position p);

    void useAbility(uint8_t ability_id);
    uint8_t getAbilityCooldown(uint8_t ability_id);

    void attacked(uint8_t damages, Unit* attacker);
    bool isDead();

protected:
    std::vector<Ability*> abilities_;

private:
    Position spawn_;
    Position current_position_;

    uint8_t life_max_;
    uint8_t life_current_;

    std::vector<Unit*> attackers_;
};

class Voleur : public Unit
{
    Voleur(Position p);
    ~Voleur();
};
#endif // !UNIT_HH_
