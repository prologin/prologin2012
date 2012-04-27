#include <cstdint>

#include <rules/player.hh>
#include <utils/log.hh>

#include "game.hh"
#include "map.hh"
#include "unit.hh"
#include "ability.hh"
#include "cell.hh"

GameState::GameState(Map* map, rules::Players_sptr players)
    : rules::GameState(),
      map_(map),
      players_(players),
      pendingMoves_(),
      game_phase_(PHASE_PLACEMENT),
      current_turn_(0)
{
}

GameState::GameState(const GameState& st)
    : rules::GameState(st),
      map_(new Map(*st.map_)),
      players_(st.players_),
      units_(st.units_),
      remote_vision_(st.remote_vision_),
      pendingMoves_(st.pendingMoves_),
      pendingAttacks_(st.pendingAttacks_),
      pendingBastoooon_(st.pendingBastoooon_),
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
    DEBUG("GameState::init");
    size_t player_count = getPlayerCount();
    for (uint32_t player_id = 0; player_id < player_count; ++player_id)
    {
        // add units and abilities
        units_.push_back(Unit_sptr(new Voleur(player_id)));
        units_.push_back(Unit_sptr(new Barbare(player_id)));
        units_.push_back(Unit_sptr(new Elfe(player_id)));

        // create palantir
        DEBUG("REMOTE VISION");
        remote_vision_.push_back(remote_vision
                {
                    .palantir_activated = false,
                    .palantir_location = {0, 0},
                    .elfe_vision_activated = false,
                    .elfe_vision_location = {0, 0}
                });
    }

    position starting_pos = map_->getStartingPos();
    Cell* starting_cell = map_->getCell(starting_pos);
    for (auto it = units_.begin(); it != units_.end(); ++it)
    {
        starting_cell->addUnit(unit_info {
                .player_id = (*it)->getPlayer(),
                .classe = (*it)->getClasse()
                });
        (*it)->setPosition(starting_pos);
        (*it)->setSpawn(starting_pos);
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

bool GameState::isPalantirActivated(int player_id) const
{
    CHECK((size_t)player_id < getPlayerCount());
    return remote_vision_[player_id].palantir_activated;
}

position GameState::getPalantir(int player_id) const
{
    CHECK((size_t)player_id < getPlayerCount());
    return remote_vision_[player_id].palantir_location;
}

void GameState::setPalantir(int player_id, position target)
{
    CHECK((size_t)player_id < getPlayerCount());
    remote_vision_[player_id].palantir_activated = true;
    remote_vision_[player_id].palantir_location = target;
}

/*
 * end Palantir
 ******************************************************************************/

/*******************************************************************************
 * ElfeVision
 */

bool GameState::isElfeVisionActivated(int player_id) const
{
    CHECK((size_t)player_id < getPlayerCount());
    return remote_vision_[player_id].elfe_vision_activated;
}

position GameState::getElfeVision(int player_id) const
{
    CHECK((size_t)player_id < getPlayerCount());
    return remote_vision_[player_id].elfe_vision_location;
}

void GameState::setElfeVision(int player_id, position target)
{
    CHECK((size_t)player_id < getPlayerCount());
    remote_vision_[player_id].elfe_vision_activated = true;
    remote_vision_[player_id].elfe_vision_location = target;
}

void GameState::deactivateElfeVision(int player_id)
{
    CHECK((size_t)player_id < getPlayerCount());
    remote_vision_[player_id].elfe_vision_activated = false;
}

/*
 * end ElfeVision
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

size_t GameState::getPlayerCount() const
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
    for (auto unit : units_)
      unit->decrementAbilitiesCooldown();
}

void GameState::setPhase(game_phase phase)
{
    game_phase_ = phase;
}

game_phase GameState::getPhase() const
{
    return game_phase_;
}

bool GameState::isFinished()
{
    return current_turn_ == map_->getMaxTurns();
}

std::vector<std::vector<std::pair<position, const ActionMove*>>>& GameState::getPendingMoves()
{
    return pendingMoves_;
}

std::list<const ActionAttack*>& GameState::getPendingAttacks()
{
    return pendingAttacks_;
}

std::list<const ActionAttack*>& GameState::getPendingBastoooon()
{
  return pendingBastoooon_;
}
