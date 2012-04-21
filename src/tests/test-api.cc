#include <sstream>

#include <gtest/gtest.h>

#include "../api.hh"
#include "../map.hh"
#include "../game.hh"
#include "../constant.hh"

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

        api_ = new Api(gamestate_, NULL);
    }

    virtual void TearDown()
    {
         delete gamestate_;
         delete api_;
    }

    std::stringstream f;

    Api* api_;
    Map* map_;
    GameState* gamestate_;
};

TEST_F(ApiTest, carte_taille)
{
    position taille = api_->carte_taille();
    EXPECT_EQ(10, taille.x);
    EXPECT_EQ(9, taille.y);
}

TEST_F(ApiTest, carte_zone_type)
{
    EXPECT_EQ(ZONE_ERREUR, api_->carte_zone_type(position {42, 42}));
    EXPECT_EQ(ZONE_MUR, api_->carte_zone_type(position {0, 0}));
    EXPECT_EQ(ZONE_FORET, api_->carte_zone_type(position {1, 1}));
    EXPECT_EQ(ZONE_HERBE, api_->carte_zone_type(position {5, 1}));
    EXPECT_EQ(ZONE_TOUR, api_->carte_zone_type(position {7, 2}));
    EXPECT_EQ(ZONE_ROUTE, api_->carte_zone_type(position {4, 2}));
    EXPECT_EQ(ZONE_MARAIS, api_->carte_zone_type(position {1, 5}));
}

TEST_F(ApiTest, carte_zone_cadavre)
{
    // TODO: check after end of turn
    EXPECT_FALSE(api_->carte_zone_cadavre(position {1, 1}));
}

TEST_F(ApiTest, carte_zone_perso)
{
    EXPECT_EQ((size_t)6, api_->carte_zone_perso(position {5, 4}).size());
}

