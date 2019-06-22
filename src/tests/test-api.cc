#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "../api.hh"
#include "../constant.hh"
#include "../game.hh"
#include "../map.hh"
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
            new rules::Players{std::vector<rules::Player_sptr>{
                rules::Player_sptr(new rules::Player(0, 0)),
                rules::Player_sptr(new rules::Player(1, 0)),
            }});

        auto gamestate = std::make_unique<GameState>(map_, players);
        gamestate->init();

        auto api_ =
            std::make_unique<Api>(std::move(gamestate), players->players[0], 0);

        rules_ = std::make_unique<Rules>(players, std::move(api_));
    }

    std::stringstream f;

    Map* map_;
    std::unique_ptr<Rules> rules_;
};

TEST_F(ApiTest, carte_taille)
{
    position taille = rules_->api().carte_taille();
    EXPECT_EQ(10, taille.x);
    EXPECT_EQ(9, taille.y);
}

TEST_F(ApiTest, carte_zone_type)
{
    EXPECT_EQ(ZONE_ERREUR, rules_->api().carte_zone_type(position{42, 42}));
    EXPECT_EQ(ZONE_MUR, rules_->api().carte_zone_type(position{0, 0}));
    EXPECT_EQ(ZONE_FORET, rules_->api().carte_zone_type(position{1, 1}));
    EXPECT_EQ(ZONE_HERBE, rules_->api().carte_zone_type(position{5, 1}));
    EXPECT_EQ(ZONE_TOUR, rules_->api().carte_zone_type(position{7, 2}));
    EXPECT_EQ(ZONE_ROUTE, rules_->api().carte_zone_type(position{4, 2}));
    EXPECT_EQ(ZONE_MARAIS, rules_->api().carte_zone_type(position{1, 5}));
}

TEST_F(ApiTest, carte_zone_perso)
{
    std::vector<perso_info> persos =
        rules_->api().carte_zone_perso(position{5, 4});
    EXPECT_EQ((size_t)6, persos.size());
    EXPECT_EQ(0, persos[0].equipe);
}

TEST_F(ApiTest, chemin)
{
    position start({1, 1}), end({1, 1});
    EXPECT_EQ((size_t)0, rules_->api().chemin(start, end).size());

    end = {1, 2};
    EXPECT_EQ((size_t)1, rules_->api().chemin(start, end).size());

    start = {0, 0};
    end = {0, 1};
    EXPECT_EQ((size_t)0, rules_->api().chemin(start, end).size());

    start = {0, 0};
    end = {0, 6};
    EXPECT_EQ((size_t)0, rules_->api().chemin(start, end).size());

    start = {7, 8};
    end = {7, 6};
    EXPECT_EQ((size_t)0, rules_->api().chemin(start, end).size());
}

TEST_F(ApiTest, perso_deplace)
{
    erreur err;
    err = rules_->api().perso_deplace(
        perso_info{0, PERSO_ELFE, 10 /* dummy */, ORIENTATION_NORD /* dummy */},
        rules_->api().chemin(map_->getStartingPos(), position{5, 2}),
        ORIENTATION_SUD);

    EXPECT_EQ(OK, err);

    err = rules_->api().perso_deplace(
        perso_info{0, PERSO_VOLEUR, 10 /* dummy */,
                   ORIENTATION_NORD /* dummy */},
        rules_->api().chemin(map_->getStartingPos(), position{4, 5}),
        ORIENTATION_EST);

    EXPECT_EQ(OK, err);

    for (auto& move : rules_->api().actions()->actions())
        rules_->api().game_state_apply(move);

    rules_->resolve_moves();

    EXPECT_EQ(4u, rules_->api().carte_zone_perso(position{5, 4}).size());
    EXPECT_EQ(1u, rules_->api().carte_zone_perso(position{5, 2}).size());
    EXPECT_EQ(1u, rules_->api().carte_zone_perso(position{4, 5}).size());

    Unit_sptr elfe = rules_->game_state().getUnit(unit_info{0, PERSO_ELFE});
    position test_elfe_pos = elfe->getPosition();
    position elfe_pos = {5, 2};
    EXPECT_EQ(elfe_pos.x, test_elfe_pos.x);
    EXPECT_EQ(elfe_pos.y, test_elfe_pos.y);
    EXPECT_EQ(ORIENTATION_SUD, elfe->getOrientation());

    Unit_sptr voleur = rules_->game_state().getUnit(unit_info{0, PERSO_VOLEUR});
    position test_voleur_pos = voleur->getPosition();
    position voleur_pos = {4, 5};
    EXPECT_EQ(voleur_pos, test_voleur_pos);
    EXPECT_EQ(ORIENTATION_EST, voleur->getOrientation());
}

TEST_F(ApiTest, perso_deplace_chemin_impossible)
{

    erreur err = rules_->api().perso_deplace(
        perso_info{0, PERSO_ELFE, 10 /* dummy */, ORIENTATION_NORD /* dummy */},
        rules_->api().chemin(map_->getStartingPos(), position{1, 1}),
        ORIENTATION_SUD);

    EXPECT_EQ(CHEMIN_IMPOSSIBLE, err);

    rules_->resolve_moves();

    // no duplicate
    EXPECT_EQ(6u, rules_->api().carte_zone_perso(position{5, 4}).size());
}

TEST_F(ApiTest, perso_deplace_bad_phase)
{
    rules_->game_state().setPhase(PHASE_ATTAQUE);

    erreur err = rules_->api().perso_deplace(
        perso_info{0, PERSO_ELFE, 10, ORIENTATION_NORD},
        rules_->api().chemin(map_->getStartingPos(), position{5, 2}),
        ORIENTATION_SUD);

    EXPECT_EQ(CHEMIN_IMPOSSIBLE, err);

    rules_->resolve_moves();

    // no duplicate
    EXPECT_EQ(6u, rules_->api().carte_zone_perso(position{5, 4}).size());
}

TEST_F(ApiTest, perso_deplace_meme_case)
{
    erreur err = rules_->api().perso_deplace(
        perso_info{0, PERSO_ELFE, 10 /* dummy */, ORIENTATION_NORD /* dummy */},
        rules_->api().chemin(map_->getStartingPos(), position{5, 4}),
        ORIENTATION_SUD);

    EXPECT_EQ(OK, err);

    rules_->resolve_moves();

    // no duplicate
    EXPECT_EQ(6u, rules_->api().carte_zone_perso(position{5, 4}).size());
}

TEST_F(ApiTest, perso_penombre)
{
    erreur err = rules_->api().perso_deplace(
        perso_info{0, PERSO_ELFE, 10, ORIENTATION_NORD},
        rules_->api().chemin(map_->getStartingPos(), position{5, 2}),
        ORIENTATION_SUD);

    EXPECT_EQ(OK, err);

    for (auto& move : rules_->api().actions()->actions())
        rules_->api().game_state_apply(move);

    rules_->resolve_moves();

    std::vector<position> p = rules_->api().perso_penombre(
        perso_info{0, PERSO_VOLEUR, 10, ORIENTATION_NORD});

    EXPECT_EQ(4u, p.size());
    EXPECT_TRUE(p[0].x == 5 && p[0].y == 4);
    EXPECT_TRUE(p[1].x == 5 && p[1].y == 3);
    EXPECT_TRUE(p[2].x == 5 && p[2].y == 4);
    EXPECT_TRUE(p[3].x == 5 && p[3].y == 2);
}

TEST_F(ApiTest, perso_vision)
{
    EXPECT_EQ(17u, rules_->api()
                       .perso_vision(perso_info{.equipe = 0,
                                                .classe = PERSO_VOLEUR,
                                                .vie = 10,
                                                .direction = ORIENTATION_NORD})
                       .size());
}

TEST_F(ApiTest, perso_vision_personnages)
{
    EXPECT_EQ(1u, rules_->api()
                      .perso_vision_personnages(
                          perso_info{.equipe = 0,
                                     .classe = PERSO_VOLEUR,
                                     .vie = 10,
                                     .direction = ORIENTATION_NORD})
                      .size());
}

TEST_F(ApiTest, palantir_vision)
{
    EXPECT_FALSE(rules_->game_state().isPalantirActivated(0));
    EXPECT_EQ(0u, rules_->api().palantir_vision().size());

    rules_->game_state().setPhase(PHASE_ATTAQUE);
    perso_info voleur = perso_info{.equipe = 0,
                                   .classe = PERSO_VOLEUR,
                                   .vie = 10,
                                   .direction = ORIENTATION_NORD};
    rules_->api().perso_attaque(voleur, ATTAQUE_PALANTIR, position{5, 4});
    for (auto& attack : rules_->api().actions()->actions())
        rules_->api().game_state_apply(attack);

    rules_->resolve_attacks();
    rules_->game_state().setPhase(PHASE_PLACEMENT);

    EXPECT_TRUE(rules_->game_state().isPalantirActivated(0));
    EXPECT_EQ(1u, rules_->api().palantir_vision().size());
}

TEST_F(ApiTest, elfe_vision)
{
    EXPECT_FALSE(rules_->game_state().isElfeVisionActivated(0));
    EXPECT_EQ(0u, rules_->api().elfe_vision().size());

    rules_->game_state().setPhase(PHASE_ATTAQUE);
    perso_info elfe = perso_info{.equipe = 0,
                                 .classe = PERSO_ELFE,
                                 .vie = 10,
                                 .direction = ORIENTATION_NORD};
    rules_->api().perso_attaque(elfe, ATTAQUE_I_SEE, position{5, 4});
    for (auto& attack : rules_->api().actions()->actions())
        rules_->api().game_state_apply(attack);

    rules_->resolve_attacks();
    rules_->game_state().setPhase(PHASE_PLACEMENT);

    EXPECT_TRUE(rules_->game_state().isElfeVisionActivated(0));
    EXPECT_EQ(1u, rules_->api().elfe_vision().size());
}

TEST_F(ApiTest, perso_attaque_recharge)
{
    perso_info elfe = perso_info{.equipe = 0,
                                 .classe = PERSO_ELFE,
                                 .vie = 10,
                                 .direction = ORIENTATION_NORD};
    EXPECT_EQ(0, rules_->api().perso_attaque_recharge(elfe, ATTAQUE_I_SEE));

    rules_->game_state().setPhase(PHASE_ATTAQUE);
    rules_->api().perso_attaque(elfe, ATTAQUE_I_SEE, position{5, 4});
    for (auto& attack : rules_->api().actions()->actions())
        rules_->api().game_state_apply(attack);

    rules_->resolve_attacks();
    rules_->game_state().setPhase(PHASE_PLACEMENT);
    EXPECT_EQ(5, rules_->api().perso_attaque_recharge(elfe, ATTAQUE_I_SEE));

    // fake turns
    for (int i = 0; i < 3; ++i)
        rules_->resolve_end_of_attaque_phase();

    EXPECT_EQ(2, rules_->api().perso_attaque_recharge(elfe, ATTAQUE_I_SEE));

    for (int i = 0; i < 3; ++i)
        rules_->resolve_end_of_attaque_phase();

    EXPECT_EQ(0, rules_->api().perso_attaque_recharge(elfe, ATTAQUE_I_SEE));
}

TEST_F(ApiTest, mon_equipe)
{
    EXPECT_EQ(0, rules_->api().mon_equipe());
}

TEST_F(ApiTest, scores)
{
    std::vector<int> default_scores(rules_->api().nombre_equipes(), 0);
    std::vector<int> actual_scores = rules_->api().scores();

    for (int i = 0; i < rules_->api().nombre_equipes(); ++i)
        EXPECT_EQ(default_scores[i], actual_scores[i]);

    rules_->game_state().setPhase(PHASE_ATTAQUE);
    perso_info voleur = perso_info{.equipe = 0,
                                   .classe = PERSO_VOLEUR,
                                   .vie = 10,
                                   .direction = ORIENTATION_NORD};
    rules_->api().perso_attaque(voleur, ATTAQUE_TRAITRISE, position{5, 4});
    for (auto& attack : rules_->api().actions()->actions())
        rules_->api().game_state_apply(attack);

    rules_->resolve_attacks();
    rules_->resolve_points();
    rules_->resolve_end_of_attaque_phase();

    actual_scores = rules_->api().scores();

    EXPECT_EQ(-3, actual_scores[1]);
    EXPECT_EQ(3, actual_scores[0]);
}

TEST_F(ApiTest, nombre_equipes)
{
    EXPECT_EQ(2, rules_->api().nombre_equipes());
}

TEST_F(ApiTest, tour_actuel)
{
    EXPECT_EQ(0, rules_->api().tour_actuel());

    for (int i = 0; i < 3; ++i)
        rules_->resolve_end_of_placement_turn();

    EXPECT_EQ(3, rules_->api().tour_actuel());

    for (int i = 0; i < 7; ++i)
        rules_->resolve_end_of_placement_turn();

    EXPECT_EQ(PHASE_DEPLACEMENT, rules_->api().game_state().getPhase());

    for (int i = 0; i < 10; ++i)
        rules_->resolve_end_of_attaque_phase();

    EXPECT_TRUE(rules_->api().game_state().isFinished());
}

TEST_F(ApiTest, perso_deplace_vide)
{
    std::vector<position> path;
    rules_->api().perso_deplace(rules_->api().perso_classe_info(PERSO_VOLEUR),
                                path, ORIENTATION_OUEST);

    for (auto& move : rules_->api().actions()->actions())
        rules_->api().game_state_apply(move);

    rules_->resolve_moves();

    EXPECT_EQ(rules_->api().perso_classe_info(PERSO_VOLEUR).direction,
              ORIENTATION_OUEST);
}
