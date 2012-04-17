#include <gtest/gtest.h>

#include "../unit.hh"
#include "../map.hh"

TEST(UnitBasic, UnitCreate) {
    Unit u(Position (0, 0));
    SUCCEED();
}

