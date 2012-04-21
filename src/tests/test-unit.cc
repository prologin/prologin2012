#include <gtest/gtest.h>

#include "../unit.hh"
#include "../map.hh"

TEST(Unit, UnitCreate)
{
    Unit u(0, 1);
    ASSERT_EQ(10, u.getCurrentLife()) << "Default life is not 10";
}

TEST(Unit, UnitDamage)
{
    Unit u0(0, 1), u1(0, 1);

    u0.attacked(3, &u1);
    ASSERT_EQ((uint8_t)7, u0.getCurrentLife());
    ASSERT_EQ((size_t)1, u0.getAttackers().size());
}

TEST(Unit, UnitDie)
{
    Unit u0(0, 1), u1(0, 1);

    u0.attacked(10, &u1);
    ASSERT_TRUE(u0.isDead());
    ASSERT_EQ((size_t)1, u0.getAttackers().size());
}
