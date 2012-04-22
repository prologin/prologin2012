#include <cstdint>

#include <rules/player.hh>

#include "game.hh"
#include "map.hh"
#include "unit.hh"

GameState::GameState(const GameState& copy_from)
    : player_count_(copy_from.player_count_)
{
}

GameState::~GameState()
{
    delete map_;
}

void GameState::init()
{
    size_t player_count = getPlayerCount();
    for (uint32_t player_id = 0; player_id < player_count; ++player_id)
    {
        rules::Player_sptr p(new rules::Player(player_id, 0));
        players_.push_back(p);

        // Add units and abilities
        units_.push_back(Unit_sptr(new Voleur(player_id)));
        units_.push_back(Unit_sptr(new Barbare(player_id)));
        units_.push_back(Unit_sptr(new Elfe(player_id)));
    }

    Cell* starting_cell = map_->getCell(map_->getStartingPos());
    for (auto it = units_.begin(); it != units_.end(); ++it)
    {
        starting_cell->addUnit(unit_info {
                .player_id = (*it)->getPlayer(),
                .classe = (*it)->getClasse()
                });
    }

    // Initialize the shortest path calcul
    map_->calculateShortestPaths();
}

rules::GameState* GameState::copy() const { return new GameState(*this); }

Map* GameState::getMap() const
{
    return map_;
}

size_t GameState::getPlayerCount()
{
    return player_count_;
}

Unit_sptr GameState::getUnit(unit_info perso) const
{
    // tricky, but works, as long as the Units on GameState::init are created
    // with the same order as perso_class enum members
    return units_[perso.player_id * 3 + perso.classe];
}
