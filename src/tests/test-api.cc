#include <sstream>

#include <gtest/gtest.h>

#include "../api.hh"
#include "../map.hh"
#include "../game.hh"
#include "../constant.hh"

extern Api* api;

class ApiTest : public ::testing::Test
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

        Api(gamestate_, NULL);
    }

    virtual void TearDown()
    {
         delete gamestate_;
         delete map_;
    }

    std::stringstream f;

    Map* map_;
    GameState* gamestate_;
};

TEST_F(ApiTest, carte_taille)
{
    position taille = api->carte_taille();
    EXPECT_EQ(10, taille.x);
    EXPECT_EQ(9, taille.y);
}

TEST_F(ApiTest, carte_zone_type)
{
    EXPECT_EQ(ZONE_MUR, api->carte_zone_type(position {0, 0}));
}
