#include <sstream>

#include <gtest/gtest.h>

#include "utils/log.hh"
#include "../constant.hh"
#include "../unit.hh"
#include "../map.hh"

class MapTest : public ::testing::Test
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
    }

    std::stringstream f;
};

TEST_F(MapTest, MapCreateFromFile)
{

    Map map;
    int err;
    if ((err = map.load(f)) != 0)
        FAIL() << "Map::load() returned " << err;

    EXPECT_EQ(9, map.getHeight());
    EXPECT_EQ(10, map.getWidth());

    position start = map.getStartingPos();
    EXPECT_EQ(5, start.x);
    EXPECT_EQ(4, start.y);

    EXPECT_EQ(ZONE_MUR, map.getCell(position {0, 0})->getType())
        << "Cell (0, 0) has a bad type";

    EXPECT_EQ(ZONE_FORET, map.getCell(position {1, 1})->getType())
        << "Cell (1, 1) has a bad type";

    EXPECT_EQ(ZONE_ROUTE, map.getCell(position {4, 1})->getType())
        << "Cell (4, 1) has a bad type";

    EXPECT_EQ(ZONE_TOUR, map.getCell(position {7, 2})->getType())
        << "Cell (7, 2) has a bad type";

    EXPECT_EQ(ZONE_MARAIS, map.getCell(position {2, 5})->getType())
        << "Cell (2, 5) has a bad type";
}

TEST_F(MapTest, MapPositionValid)
{
    Map map;
    map.load(f);

    EXPECT_TRUE(map.isPositionValid(position {0, 0}));

    EXPECT_FALSE(map.isPositionValid(position {11, 2}));
    EXPECT_FALSE(map.isPositionValid(position {-1, 42}));
}

TEST_F(MapTest, MapMoveUnit)
{
    Map map;
    map.load(f);

    Unit_sptr u0(new Unit(0, 1));
    map.getCell(position {1, 1})->addUnit(u0);
    map.moveUnit(u0, position {1, 1}, position {1, 2});

    // check unit not in cell
    ASSERT_EQ(PERSONNAGE_IMPOSSIBLE, map.checkMove(u0,
                path_t {position {1, 1}, position {2, 1}}));

    // check bad position
    ASSERT_EQ(POSITION_IMPOSSIBLE, map.checkMove(u0,
                path_t {position {1, 2}, position {42, 42}}));

    ASSERT_EQ(OK, map.checkMove(u0, path_t {position {1, 2}, position {1, 3}}));

    ASSERT_FALSE(map.getCell(position {0, 0})->isUnitOnCell(u0));
    ASSERT_TRUE(map.getCell(position {1, 2})->isUnitOnCell(u0));
}
