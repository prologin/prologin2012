#include <gtest/gtest.h>

#include "../unit.hh"
#include "../cell.hh"

TEST(CellBasic, CellUnitManagement) {
    Position start(0, 0);
    Unit u0(start), u1(start);
    Grass c(0, 0);

    ASSERT_EQ(0, c.getPopulation()) << "Empty cell population is not 0";

    c.addUnit(&u0);
    ASSERT_EQ(1, c.getPopulation()) << "Cell population with one unit is not 1";

    ASSERT_EQ(1, c.removeUnit(&u1)) << "Removing an unit not on this cell did "
                                    << "not fail";

    ASSERT_EQ(0, c.removeUnit(&u0)) << "Removing an unit in this cell did not "
                                    << "decrease population";
}

