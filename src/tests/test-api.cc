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
        utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;

        f << "10 9\n";
        f << "5 4\n";
        f << "10\n";
        f << "20\n";
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

        api_ = new Api(gamestate_, players->players[0], 0);

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
    api_->perso_deplace(
        perso_info {0, PERSO_ELFE, 10 /* dummy */, ORIENTATION_NORD /* dummy */},
        api_->chemin(map_->getStartingPos(), position {5, 2}),
        ORIENTATION_SUD
    );

    api_->perso_deplace(
        perso_info {0, PERSO_VOLEUR, 10 /* dummy */, ORIENTATION_NORD /* dummy */},
        api_->chemin(map_->getStartingPos(), position {4, 5}),
        ORIENTATION_EST
    );

    for (auto& move : api_->actions()->actions())
        api_->game_state_set(move->apply(api_->game_state()));

    gamestate_ = api_->game_state();
    rules_->resolve_moves();

    Unit_sptr elfe = gamestate_->getUnit(unit_info {0, PERSO_ELFE});
    position test_elfe_pos = elfe->getPosition();
    position elfe_pos = {5, 2};
    EXPECT_EQ(elfe_pos.x, test_elfe_pos.x);
    EXPECT_EQ(elfe_pos.y, test_elfe_pos.y);
    EXPECT_EQ(ORIENTATION_SUD, elfe->getOrientation());

    Unit_sptr voleur = gamestate_->getUnit(unit_info {0, PERSO_VOLEUR});
    position test_voleur_pos = voleur->getPosition();
    position voleur_pos = {4, 5};
    EXPECT_EQ(voleur_pos, test_voleur_pos);
    EXPECT_EQ(ORIENTATION_EST, voleur->getOrientation());
}

TEST_F(ApiTest, perso_deplace_chemin_impossible)
{

    erreur err = api_->perso_deplace(
        perso_info {0, PERSO_ELFE, 10 /* dummy */, ORIENTATION_NORD /* dummy */},
        api_->chemin(map_->getStartingPos(), position {1, 1}),
        ORIENTATION_SUD
    );

    EXPECT_EQ(CHEMIN_IMPOSSIBLE, err);
}

TEST_F(ApiTest, perso_deplace_bad_phase)
{
    gamestate_->setPhase(PHASE_ATTAQUE);

    erreur err = api_->perso_deplace(
        perso_info {0, PERSO_ELFE, 10, ORIENTATION_NORD},
        api_->chemin(map_->getStartingPos(), position {5, 2}),
        ORIENTATION_SUD
    );

    EXPECT_EQ(CHEMIN_IMPOSSIBLE, err);
}

TEST_F(ApiTest, perso_penombre)
{
    api_->perso_deplace(
        perso_info {0, PERSO_ELFE, 10, ORIENTATION_NORD},
        api_->chemin(map_->getStartingPos(), position {5, 2}),
        ORIENTATION_SUD
    );

    for (auto& move : api_->actions()->actions())
        api_->game_state_set(move->apply(api_->game_state()));

    gamestate_ = api_->game_state();

    rules_->resolve_moves();

    std::vector<position> p = api_->perso_penombre(perso_info {0, PERSO_VOLEUR, 10, ORIENTATION_NORD});

    EXPECT_EQ(4u, p.size());
    EXPECT_TRUE(p[0].x == 5 && p[0].y == 4);
    EXPECT_TRUE(p[1].x == 5 && p[1].y == 3);
    EXPECT_TRUE(p[2].x == 5 && p[2].y == 4);
    EXPECT_TRUE(p[3].x == 5 && p[3].y == 2);
}

TEST_F(ApiTest, perso_vision)
{
    EXPECT_EQ(17u, api_->perso_vision(
        perso_info
        {
            .equipe = 0,
            .classe = PERSO_VOLEUR,
            .vie = 10,
            .direction = ORIENTATION_NORD
        }).size());
}

TEST_F(ApiTest, perso_vision_ennemis)
{
    EXPECT_EQ(1u, api_->perso_vision_ennemis(
        perso_info
        {
            .equipe = 0,
            .classe = PERSO_VOLEUR,
            .vie = 10,
            .direction = ORIENTATION_NORD
        }).size());
}

TEST_F(ApiTest, palantir_vision)
{
    EXPECT_FALSE(gamestate_->isPalantirActivated(0));
    EXPECT_EQ(0u, api_->palantir_vision().size());

    gamestate_->setPhase(PHASE_ATTAQUE);
    perso_info voleur = perso_info
        {
            .equipe = 0,
            .classe = PERSO_VOLEUR,
            .vie = 10,
            .direction = ORIENTATION_NORD
        };
    api_->perso_attaque(voleur, ATTAQUE_PALANTIR, position {5, 4});
    for (auto& attack : api_->actions()->actions())
        api_->game_state_set(attack->apply(api_->game_state()));

    gamestate_ = api_->game_state();

    rules_->resolve_attacks();
    gamestate_->setPhase(PHASE_PLACEMENT);

    EXPECT_TRUE(gamestate_->isPalantirActivated(0));
    EXPECT_EQ(1u, api_->palantir_vision().size());
}

TEST_F(ApiTest, elfe_vision)
{
    EXPECT_FALSE(gamestate_->isElfeVisionActivated(0));
    EXPECT_EQ(0u, api_->elfe_vision().size());

    gamestate_->setPhase(PHASE_ATTAQUE);
    perso_info elfe = perso_info
        {
            .equipe = 0,
            .classe = PERSO_ELFE,
            .vie = 10,
            .direction = ORIENTATION_NORD
        };
    api_->perso_attaque(elfe, ATTAQUE_I_SEE, position {5, 4});
    for (auto& attack : api_->actions()->actions())
        api_->game_state_set(attack->apply(api_->game_state()));

    gamestate_ = api_->game_state();

    rules_->resolve_attacks();
    gamestate_->setPhase(PHASE_PLACEMENT);

    EXPECT_TRUE(gamestate_->isElfeVisionActivated(0));
    EXPECT_EQ(1u, api_->elfe_vision().size());
}

TEST_F(ApiTest, perso_attaque_recharge)
{
    perso_info elfe = perso_info
        {
            .equipe = 0,
            .classe = PERSO_ELFE,
            .vie = 10,
            .direction = ORIENTATION_NORD
        };
    EXPECT_EQ(0, api_->perso_attaque_recharge(elfe, ATTAQUE_I_SEE));

    gamestate_->setPhase(PHASE_ATTAQUE);
    api_->perso_attaque(elfe, ATTAQUE_I_SEE, position {5, 4});
    for (auto& attack : api_->actions()->actions())
        api_->game_state_set(attack->apply(api_->game_state()));

    gamestate_ = api_->game_state();

    rules_->resolve_attacks();
    gamestate_->setPhase(PHASE_PLACEMENT);
    EXPECT_EQ(5, api_->perso_attaque_recharge(elfe, ATTAQUE_I_SEE));

    // fake turns
    for (int i = 0; i < 3; ++i)
        rules_->resolve_end_of_attaque_phase();

    EXPECT_EQ(2, api_->perso_attaque_recharge(elfe, ATTAQUE_I_SEE));

    for (int i = 0; i < 3; ++i)
        rules_->resolve_end_of_attaque_phase();

    EXPECT_EQ(0, api_->perso_attaque_recharge(elfe, ATTAQUE_I_SEE));

}

TEST_F(ApiTest, mon_equipe)
{
    EXPECT_EQ(0, api_->mon_equipe());
}

TEST_F(ApiTest, scores)
{
    std::vector<int> default_scores(api_->nombre_equipes(), 0);
    std::vector<int> actual_scores = api_->scores();

    for (int i = 0; i < api_->nombre_equipes(); ++i)
        EXPECT_EQ(default_scores[i], actual_scores[i]);

    gamestate_->setPhase(PHASE_ATTAQUE);
    perso_info voleur = perso_info
        {
            .equipe = 0,
            .classe = PERSO_VOLEUR,
            .vie = 10,
            .direction = ORIENTATION_NORD
        };
    api_->perso_attaque(voleur, ATTAQUE_TRAITRISE, position {5, 4});
    for (auto& attack : api_->actions()->actions())
        api_->game_state_set(attack->apply(api_->game_state()));

    gamestate_ = api_->game_state();

    rules_->resolve_attacks();
    rules_->resolve_points();
    rules_->resolve_end_of_attaque_phase();

    actual_scores = api_->scores();

    EXPECT_EQ(-3, actual_scores[1]);
    EXPECT_EQ(3, actual_scores[0]);

}

TEST_F(ApiTest, nombre_equipes)
{
    EXPECT_EQ(2, api_->nombre_equipes());
}

TEST_F(ApiTest, tour_actuel)
{
    EXPECT_EQ(0, api_->tour_actuel());

    for (int i = 0; i < 3; ++i)
        rules_->resolve_end_of_placement_turn();

    EXPECT_EQ(3, api_->tour_actuel());

    for (int i = 0; i < 7; ++i)
        rules_->resolve_end_of_placement_turn();

    EXPECT_EQ(PHASE_DEPLACEMENT, api_->game_state()->getPhase());

    for (int i = 0; i < 10; ++i)
        rules_->resolve_end_of_attaque_phase();

    EXPECT_TRUE(api_->game_state()->isFinished());

}
