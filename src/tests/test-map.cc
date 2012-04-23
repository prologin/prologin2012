#include <sstream>
#include <iostream>

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
    unit_info ui0 = u0->getUnitInfo();

    map.getCell(position {1, 1})->addUnit(ui0);
    map.moveUnit(ui0, position {1, 1}, position {1, 2});

    // check unit not in cell
    ASSERT_EQ(PERSONNAGE_IMPOSSIBLE, map.checkMove(ui0,
                path_t {position {1, 1}, position {2, 1}}));

    // check bad position
    ASSERT_EQ(POSITION_IMPOSSIBLE, map.checkMove(ui0,
                path_t {position {1, 2}, position {42, 42}}));

    ASSERT_EQ(OK, map.checkMove(ui0, path_t {position {1, 2}, position {1, 3}}));

    ASSERT_FALSE(map.getCell(position {0, 0})->isUnitOnCell(ui0));
    ASSERT_TRUE(map.getCell(position {1, 2})->isUnitOnCell(ui0));
}

TEST_F(MapTest, MapGetPath)
{
  Map map;
  map.load(f);
  map.calculateShortestPaths();

  std::vector<position> path1 = map.getPath(position({0,0}), position({1,1}));
  std::vector<position> path2 = map.getPath(position({5,5}), position({1,1}));

  EXPECT_TRUE(path1.empty());

  EXPECT_EQ(8, path2.size());
  EXPECT_TRUE(path2[0].x == 4 && path2[0].y == 5);
  EXPECT_TRUE(path2[1].x == 4 && path2[1].y == 4);
  EXPECT_TRUE(path2[2].x == 4 && path2[2].y == 3);
  EXPECT_TRUE(path2[3].x == 4 && path2[3].y == 2);
  EXPECT_TRUE(path2[4].x == 4 && path2[4].y == 1);
  EXPECT_TRUE(path2[5].x == 3 && path2[5].y == 1);
  EXPECT_TRUE(path2[6].x == 2 && path2[6].y == 1);
  EXPECT_TRUE(path2[7].x == 1 && path2[7].y == 1);
}

TEST_F(MapTest, MapGetSurroundings)
{
  Map map;
  map.load(f);
  Unit_sptr u0(new Unit(0, 1));
  unit_info ui0 = u0->getUnitInfo();

  map.getCell(position{1, 1})->addUnit(ui0);
  map.getCell(position{1, 2})->addUnit(ui0);
  map.getCell(position{1, 3})->addUnit(ui0);
  map.getCell(position{1, 4})->addUnit(ui0);
  map.getCell(position{1, 5})->addUnit(ui0);
  map.getCell(position{1, 6})->addUnit(ui0);
  map.getCell(position{1, 7})->addUnit(ui0);
  map.getCell(position{2, 2})->addUnit(ui0);
  map.getCell(position{2, 3})->addUnit(ui0);
  map.getCell(position{2, 4})->addUnit(ui0);
  map.getCell(position{2, 5})->addUnit(ui0);
  map.getCell(position{2, 6})->addUnit(ui0);
  map.getCell(position{3, 3})->addUnit(ui0);
  map.getCell(position{3, 4})->addUnit(ui0);
  map.getCell(position{3, 5})->addUnit(ui0);

  std::vector<position> pos;
  pos = map.getSurroundings(position {3,4}, ORIENTATION_OUEST, 3);

  EXPECT_EQ(pos.size(), 9);
  EXPECT_TRUE(pos[0].x == 3 && pos[0].y == 5);
  EXPECT_TRUE(pos[1].x == 3 && pos[1].y == 4);
  EXPECT_TRUE(pos[2].x == 3 && pos[2].y == 3);
  EXPECT_TRUE(pos[3].x == 2 && pos[3].y == 6);
  EXPECT_TRUE(pos[4].x == 2 && pos[4].y == 5);
  EXPECT_TRUE(pos[5].x == 2 && pos[5].y == 4);
  EXPECT_TRUE(pos[6].x == 1 && pos[6].y == 7);
  EXPECT_TRUE(pos[7].x == 1 && pos[7].y == 6);
  EXPECT_TRUE(pos[8].x == 1 && pos[8].y == 5);
}

TEST_F(MapTest, MapGetSurroundingsOnTower)
{
  Map map;
  map.load(f);
  Unit_sptr u0(new Unit(0, 1));
  unit_info ui0 = u0->getUnitInfo();

  map.getCell(position{5, 1})->addUnit(ui0);
  map.getCell(position{6, 1})->addUnit(ui0);
  map.getCell(position{7, 1})->addUnit(ui0);
  map.getCell(position{8, 1})->addUnit(ui0);
  map.getCell(position{5, 2})->addUnit(ui0);
  map.getCell(position{6, 2})->addUnit(ui0);
  map.getCell(position{7, 2})->addUnit(ui0);
  map.getCell(position{8, 2})->addUnit(ui0);
  map.getCell(position{5, 3})->addUnit(ui0);
  map.getCell(position{6, 3})->addUnit(ui0);
  map.getCell(position{7, 3})->addUnit(ui0);
  map.getCell(position{8, 3})->addUnit(ui0);

  std::vector<position> pos;
  pos = map.getSurroundings(position {7,2}, ORIENTATION_OUEST, 3);

  EXPECT_EQ(pos.size(), 12);
}
