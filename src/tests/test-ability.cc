#include <gtest/gtest.h>

#include "../ability.hh"
#include "../constant.hh"
#include "../map.hh"
#include "../game.hh"

class AbilityTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;

        f << "10 9\n";
        f << "5 4\n";
        f << "##########\n";
        f << "#FFF_....#\n";
        f << "#FFF_..T.#\n";
        f << "#FFF_....#\n";
        f << "#..._....#\n";
        f << "#~~~_....#\n";
        f << "#~T~_....#\n";
        f << "#~~~_....#\n";
        f << "##########\n";

        map_ = new Map();
        map_->load(f);
        gamestate_ = new GameState(map_, 2);

        gamestate_->init();
    }

    virtual void TearDown()
    {
         delete gamestate_;
    }

    std::stringstream f;

    Map* map_;
    GameState* gamestate_;
};

TEST_F(AbilityTest, AbilityCreate)
{
    Ability a = Ability(0);
    ASSERT_EQ(0, a.getCooldown());

    Ability b = Ability(1);
    ASSERT_EQ(0, b.getCooldown());
}

TEST_F(AbilityTest, AbilityCooldown)
{
    Ability a = Ability(1);
    a.apply(gamestate_, unit_info {0, PERSO_VOLEUR}, position {0, 0});

    EXPECT_EQ(1, a.getCooldown());

}

/*******************************************************************************
 * Test BasicAbility
 */

TEST_F(AbilityTest, BasicAbilityCheck)
{
    unit_info attacker_unit = unit_info {0, PERSO_VOLEUR};
    Unit_sptr attacker = gamestate_->getUnit(attacker_unit);

    BasicAttack attack = BasicAttack(3, 2);
    position target = position {5, 4};
    // check
    EXPECT_EQ(OK, attack.check(*gamestate_, attacker_unit, target));
    EXPECT_EQ(OK, attack.check(*gamestate_, attacker_unit, position {5, 5}));

    // target is not in range
    EXPECT_EQ(POSITION_IMPOSSIBLE,
            attack.check(*gamestate_, attacker_unit, position {1, 2}));
    EXPECT_EQ(POSITION_IMPOSSIBLE,
            attack.check(*gamestate_, attacker_unit, position {0, 3}));
}

TEST_F(AbilityTest, BasicAbilityApply)
{
    unit_info attacker_unit = unit_info {0, PERSO_VOLEUR};
    Unit_sptr attacker = gamestate_->getUnit(attacker_unit);

    BasicAttack attack = BasicAttack(3, 2);
    position target = position {5, 4};

    ASSERT_EQ(OK, attack.check(*gamestate_, attacker_unit, target));
    attack.apply(gamestate_, attacker_unit, target);

    // BasicAttack has no cooldown
    EXPECT_EQ(0, attack.getCooldown());

    UnitVect units_on_target = gamestate_->getMap()->getUnitsOn(target);
    for (auto it = units_on_target.begin(); it != units_on_target.end(); ++it)
    {
        if (*it == attacker_unit)
            EXPECT_EQ(VOLEUR_VIE, attacker->getCurrentLife());
        else
            EXPECT_EQ(7 /* _VIE - dmg = 10 - 3 */,
                    gamestate_->getUnit(*it)->getCurrentLife());
    }
}

/*******************************************************************************
 * Test Palantir
 */

TEST_F(AbilityTest, PalantirCheck)
{
    // TODO CHECK VISION;
}

TEST_F(AbilityTest, PalantirApply)
{
    unit_info attacker_unit = unit_info {0, PERSO_VOLEUR};
    position target = {5, 4};

    Palantir attack = Palantir();

    attack.apply(gamestate_, attacker_unit, target);

    EXPECT_TRUE(gamestate_->getPalantir(0).activated);
    EXPECT_EQ(target, gamestate_->getPalantir(0).location);
}
