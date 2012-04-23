#ifndef ABILITY_HH_
# define ABILITY_HH_

# include <memory>
# include <list>

# include "constant.hh"

/*******************************************************************************
 * Cooldown
 */

# define VOLEUR_PALANTIR_CD 3
# define VOLEUR_TRAITRISE_CD 8

# define BARBARE_BASTOOOON_CD 3
# define BARBARE_FUS_RO_DAH_CD 10

# define ELFE_I_SEE_CD 5
# define ELFE_LOTO_CD 8

struct unit_info;

class GameState;

class Unit;

typedef std::shared_ptr<Unit> Unit_sptr;
typedef std::vector<Unit_sptr> UnitList;

class Map;

/*******************************************************************************
 * Ability
 */

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

/*******************************************************************************
 * BasicAttack
 */

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

/*******************************************************************************
 * Voleur - Palantir
 */

typedef struct palantir
{
    bool activated;
    position location;
} palantir;

class Palantir : public Ability
{
public:
    Palantir()
        : Ability(VOLEUR_PALANTIR_CD)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

/*******************************************************************************
 * Voleur - Traitrise
 */

class Traitrise : public Ability
{
public:
    Traitrise()
        : Ability(VOLEUR_TRAITRISE_CD)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    // kill unit
    void apply(GameState* st, unit_info attacker, position target);
};

#endif // !ABILITY_HH_
