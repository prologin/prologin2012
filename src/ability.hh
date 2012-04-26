#ifndef ABILITY_HH_
# define ABILITY_HH_

# include <memory>
# include <list>

# include "constant.hh"

# define ACTION_MOVE 0
# define ACTION_ATTACK 1

struct unit_info;

class GameState;

class Unit;

typedef std::shared_ptr<Unit> Unit_sptr;
typedef std::vector<Unit_sptr> Units;

class Map;

/*******************************************************************************
 * Ability
 */

class Ability
{
public:
    Ability(int cost)
        : cooldown_(0),
          cost_(cost)
    {}

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
 * VoleurAttaque
 */

class VoleurAttaque: public Ability
{
public:
    VoleurAttaque()
        : Ability(0)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

/*******************************************************************************
 * Voleur - Palantir
 */

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

/*******************************************************************************
 * Barbare - BarbareAttaque
 */

class BarbareAttaque: public Ability
{
public:
    BarbareAttaque()
        : Ability(0)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

/*******************************************************************************
 * Barbare - Bastoooon
 */

class Bastoooon : public Ability
{
public:
    Bastoooon()
        : Ability(BARBARE_BASTOOOON_CD)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

/*******************************************************************************
 * Barbare - FusRoDah
 */

class FusRoDah: public Ability
{
public:
    FusRoDah()
        : Ability(BARBARE_FUS_RO_DAH_CD)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

/*******************************************************************************
 * Elfe - ElfeAttaque
 */

class ElfeAttaque : public Ability
{
public:
    ElfeAttaque()
        : Ability(0)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

/*******************************************************************************
 * Elfe - ISee
 */

class ISee: public Ability
{
public:
    ISee()
        : Ability(ELFE_I_SEE_CD)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

/*******************************************************************************
 * Elfe - Loto
 */

class Loto: public Ability
{
public:
    Loto()
        : Ability(ELFE_LOTO_CD)
    {}

    erreur check(const GameState& st, unit_info attacker, position target)
        const;
    void apply(GameState* st, unit_info attacker, position target);
};

#endif // !ABILITY_HH_
