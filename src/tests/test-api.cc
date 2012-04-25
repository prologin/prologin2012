#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "../api.hh"
#include "../map.hh"
#include "../game.hh"
#include "../constant.hh"
#include "../rules.hh"

class ApiTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        f << "10 9\n";
        f << "5 4\n";
        f << "10\n";
        f << "10\n";
        f << "##########\n";
        f << "#FFF_....#\n";
        f << "#FFF_..T.#\n";
        f << "#FFF_....#\n";
        f << "#..._....#\n";
        f << "#~~~_....#\n";
        f << "#~T~_..###\n";
        f << "#~~~_..#.#\n";
        f << "##########\n";

        map_ = new Map();
        map_->load(f);

        rules::Players_sptr players(
            new rules::Players
            {
                std::vector<rules::Player_sptr>
                {
                    rules::Player_sptr(new rules::Player(0, 0)),
                    rules::Player_sptr(new rules::Player(1, 0)),
                }
            }
        );

        gamestate_ = new GameState(map_, players);

        gamestate_->init();

        api_ = new Api(gamestate_, players->players[0]);

        rules_ = new Rules(players, api_);
    }

    virtual void TearDown()
    {
         delete rules_;
    }

    std::stringstream f;

    Api* api_;
    Map* map_;
    GameState* gamestate_;
    Rules* rules_;
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
    std::vector<perso_info> persos = api_->carte_zone_perso(position {5, 4});
    EXPECT_EQ((size_t)6, persos.size());
    EXPECT_EQ(0, persos[0].equipe);
}

TEST_F(ApiTest, chemin)
{
    position start({1, 1}), end({1, 1});
    EXPECT_EQ((size_t)0, api_->chemin(start, end).size());

    end = {1, 2};
    EXPECT_EQ((size_t)1, api_->chemin(start, end).size());

    start = {0, 0};
    end = {0, 1};
    EXPECT_EQ((size_t)0, api_->chemin(start, end).size());

    start = {0, 0};
    end = {0, 6};
    EXPECT_EQ((size_t)0, api_->chemin(start, end).size());

    start = {7, 8};
    end = {7, 6};
    EXPECT_EQ((size_t)0, api_->chemin(start, end).size());
}

TEST_F(ApiTest, perso_deplace)
{
    // TODO test halfr
}

TEST_F(ApiTest, perso_penombre)
{
    api_->perso_deplace(
        perso_info {0, PERSO_VOLEUR, 10, ORIENTATION_NORD},
        api_->chemin(map_->getStartingPos(), position {5, 2}),
        ORIENTATION_SUD
    );

    for (auto& move : api_->actions()->actions())
        move->apply(gamestate_);

    rules_->resolve_moves();

    //EXEPCT_EQ(...);
}

TEST_F(ApiTest, perso_vision)
{
    api_->perso_vision(
        perso_info
        {
            .equipe = 0,
            .classe = PERSO_VOLEUR,
            .vie = 10,
            .direction = ORIENTATION_NORD
        });

    // TODO Moar test

    SUCCEED();
}

TEST_F(ApiTest, scores)
{
    std::vector<int> default_scores(2, 0);
    std::vector<int> actual_scores = api_->scores();

    for (int i = 0; i < api_->nombre_equipes(); ++i)
        EXPECT_EQ(default_scores[i], actual_scores[i]);
}

TEST_F(ApiTest, nombre_equipes)
{
    EXPECT_EQ(2, api_->nombre_equipes());
}

TEST_F(ApiTest, tour_actuel)
{
    EXPECT_EQ(0, api_->tour_actuel());
}
