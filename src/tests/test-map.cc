#include <sstream>

#include <gtest/gtest.h>

#include "utils/log.hh"
#include "../unit.hh"
#include "../map.hh"

class MapTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;

        f << "10 9\n";
        f << "3\n";
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

    ASSERT_EQ((uint32_t)9, map.getHeight());
    ASSERT_EQ((uint32_t)10, map.getWidth());

    Position start = map.getStartingPos();
    ASSERT_EQ((uint32_t)5, start.x);
    ASSERT_EQ((uint32_t)4, start.y);

    ASSERT_EQ(WALL, map.getCell(Position(0, 0))->getType())
        << "Cell (0, 0) has a bad type";

    ASSERT_EQ(FOREST, map.getCell(Position(1, 1))->getType())
        << "Cell (1, 1) has a bad type";

    ASSERT_EQ(ROAD, map.getCell(Position(4, 1))->getType())
        << "Cell (4, 1) has a bad type";

    ASSERT_EQ(TOWER, map.getCell(Position(7, 2))->getType())
        << "Cell (7, 2) has a bad type";

    ASSERT_EQ(SWAMP, map.getCell(Position(2, 5))->getType())
        << "Cell (2, 5) has a bad type";
}

TEST_F(MapTest, MapPositionValid)
{
    Map map;
    map.load(f);
    ASSERT_TRUE(map.isPositionValid(Position(0, 0)));
    ASSERT_FALSE(map.isPositionValid(Position(11, 2)));
    ASSERT_FALSE(map.isPositionValid(Position(11, 42)));
}

TEST_F(MapTest, MapMoveUnit)
{
    Map map;
    map.load(f);

    Unit u0 = Unit(0);
    map.getCell(Position(1, 1))->addUnit(&u0);
    map.moveUnit(&u0, Position(1, 1), Position(1, 2));

    ASSERT_EQ(PERSONNAGE_IMPOSSIBLE, map.checkMove(&u0,
                path_t {Position(1, 1), Position(2, 1)}));

    ASSERT_EQ(POSITION_IMPOSSIBLE, map.checkMove(&u0,
                path_t {Position(1, 2), Position(42, 42)}));

    ASSERT_EQ(OK, map.checkMove(&u0, path_t {Position(1, 2), Position(1, 3)}));

    ASSERT_FALSE(map.getCell(Position(0, 0))->isUnitOnCell(&u0));
    ASSERT_TRUE(map.getCell(Position(1, 2))->isUnitOnCell(&u0));
}
