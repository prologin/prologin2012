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
}

TEST_F(AbilityTest, BasicAbility)
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
