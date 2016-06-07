#ifndef ABILITY_HH_
# define ABILITY_HH_

# include <memory>
# include <list>
# include <vector>

# include "constant.hh"

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

    virtual ~Ability()
    {}

    /* check:
     *  - cooldown > 0
     *  - target is on the map
     */
    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;

    /* apply:
     *  - add decrease life points
     */
    virtual void apply(GameState* st, unit_info attacker, position target);

    int getCooldown() const;
    void decrementCooldown();
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    // kill unit
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
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

    virtual erreur check(const GameState& st, unit_info attacker,
        position target) const;
    virtual void apply(GameState* st, unit_info attacker, position target);
};

#endif // !ABILITY_HH_
