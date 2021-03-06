#include <cstdint>

#include <gtest/gtest.h>

#include "../constant.hh"
#include "../game.hh"
#include "../map.hh"
#include "../unit.hh"

class GameTest : public ::testing::Test
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
        f << "#~T~_....#\n";
        f << "#~~~_....#\n";
        f << "##########\n";

        map_ = new Map();
        map_->load(f);

        players.add(std::make_shared<rules::Player>(0, rules::PLAYER));
        players.add(std::make_shared<rules::Player>(1, rules::PLAYER));
        players.add(std::make_shared<rules::Player>(2, rules::PLAYER));
    }

    std::stringstream f;

    Map* map_;
    rules::Players players;
};

TEST_F(GameTest, GameCreate)
{
    GameState gs = GameState(map_, players);
    gs.init();

    EXPECT_EQ((uint32_t)0, players[0]->id);
    EXPECT_EQ((uint32_t)1, players[1]->id);
    EXPECT_EQ((uint32_t)2, players[2]->id);

    EXPECT_EQ((size_t)3, gs.getPlayerCount());
    EXPECT_EQ(map_, gs.getMap());

    position starting_pos = gs.getMap()->getStartingPos();
    // starting position is set
    for (size_t i = 0; i < gs.getPlayerCount(); ++i)
    {
        position unit_pos =
            gs.getUnit(unit_info{(int)i, PERSO_VOLEUR})->getPosition();
        EXPECT_EQ(starting_pos, unit_pos);
    }
}
