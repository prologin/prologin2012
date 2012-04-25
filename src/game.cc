#include <cstdint>

#include <rules/player.hh>
#include <utils/log.hh>

#include "game.hh"
#include "map.hh"
#include "unit.hh"
#include "ability.hh"

GameState::GameState(Map* map, rules::Players_sptr players)
    : rules::GameState(),
      map_(map),
      players_(players),
      current_turn_(0)
{
}

GameState::GameState(const GameState& st)
    : rules::GameState(st),
      map_(new Map(*st.map_)),
      players_(st.players_),
      units_(st.units_),
      palantiri_(st.palantiri_),
      pendingMoves_(st.pendingMoves_),
      pendingAttacks_(st.pendingAttacks_),
      current_turn_(st.current_turn_)
{
}

rules::GameState* GameState::copy() const
{
    // NOT USED IN PROLOGIN2012
    // TEST
    return new GameState(*this);
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
        // add units and abilities
        units_.push_back(Unit_sptr(new Voleur(player_id)));
        units_.push_back(Unit_sptr(new Barbare(player_id)));
        units_.push_back(Unit_sptr(new Elfe(player_id)));

        // create palantir
        palantiri_.push_back(palantir_t
                {
                    .activated = false,
                    .location = {0, 0}
                });
    }

    Cell* starting_cell = map_->getCell(map_->getStartingPos());
    for (auto it = units_.begin(); it != units_.end(); ++it)
    {
        starting_cell->addUnit(unit_info {
                .player_id = (*it)->getPlayer(),
                .classe = (*it)->getClasse()
                });
        (*it)->setPosition(map_->getStartingPos());
    }

    // initialize the shortest path calcul
    map_->calculateShortestPaths();
}

Map* GameState::getMap() const
{
    return map_;
}

/*******************************************************************************
 * Palantir
 */

palantir_t GameState::getPalantir(int player_id) const
{
    CHECK((size_t)player_id < palantiri_.size());
    return palantiri_[player_id];
}

void GameState::setPalantir(int player_id, position target)
{
    palantiri_[player_id].activated = true;
    palantiri_[player_id].location = target;
}

/*
 * end Palantir
 ******************************************************************************/

/*******************************************************************************
 * getUnit(s)
 */

Units GameState::getUnits() const
{
    return units_;
}

Unit_sptr GameState::getUnit(unit_info perso) const
{
    // tricky, but works, as long as the Units on GameState::init are created
    // with the same order as perso_class enum members
    return units_[perso.player_id * 3 + perso.classe];
}

Unit_sptr GameState::getUnit(perso_info perso) const
{
    return getUnit(unit_info
            {
                .player_id = perso.equipe,
                .classe = perso.classe
            });
}

/*
 * end getUnit(s)
 ******************************************************************************/

size_t GameState::getPlayerCount()
{
    return players_->players.size();
}

std::vector<int> GameState::getScores() const
{
    std::vector<int> scores;
    for (auto it = players_->players.begin(); it != players_->players.end(); ++it)
    {
        scores.push_back((*it)->score);
    }

    return scores;
}

int GameState::getCurrentTurn() const
{
    return current_turn_;
}

void GameState::incrementTurn()
{
    current_turn_ += 1;
}

bool GameState::isFinished()
{
    return current_turn_ == map_->getMaxTurns();
}

std::vector<std::vector<std::pair<position, Unit_sptr>>>& GameState::getPendingMoves()
{
    return pendingMoves_;
}

std::list<const ActionAttack*>& GameState::getPendingAttacks()
{
    return pendingAttacks_;
}
