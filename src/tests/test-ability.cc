#include <gtest/gtest.h>

#include "../ability.hh"

TEST(Ability, AbilityCreate)
{
    Ability a = Ability(0);
    ASSERT_EQ(0, a.getCooldown());
}
