#include <gtest/gtest.h>

#include "../unit.hh"
#include "../cell.hh"

TEST(CellBasic, CellUnitManagement)
{
    Unit_sptr u0(new Voleur(0)), u1(new Voleur(1));
    unit_info ui0 = u0->getUnitInfo();
    unit_info ui1 = u1->getUnitInfo();

    Cell c(ZONE_HERBE);

    ASSERT_EQ(0, c.getPopulation()) << "Empty cell population is not 0";

    c.addUnit(ui0);
    ASSERT_EQ(1, c.getPopulation()) << "Cell population with one unit is not 1";

    ASSERT_EQ(1, c.removeUnit(ui1)) << "Removing an unit not on this cell did "
                                    << "not fail";

    ASSERT_TRUE(c.isUnitOnCell(ui0)) << "Unit should be on this cell";

    ASSERT_EQ(0, c.removeUnit(ui0)) << "Removing an unit in this cell did not "
                                    << "decrease population";
}

