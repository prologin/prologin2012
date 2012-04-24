#ifndef GAME_HH_
# define GAME_HH_

# include <vector>

# include <rules/game-state.hh>
# include <rules/player.hh>

# include "unit.hh"
# include "ability.hh"

class Map;

class GameState : public rules::GameState
{
public:
    GameState(Map* map, rules::PlayerVector_sptr players)
        : rules::GameState(), map_(map), players_(players), pendingMoves_(),
        current_turn_(0)
    {}

    virtual rules::GameState* copy() const;

    ~GameState();

    void init();

    void resolveMoves(); // FIXME jicks
    void resolveAttacks();

    Map* getMap() const;

    palantir getPalantir(int player_id) const;
    void setPalantir(int player_id, position target);

    Unit_sptr getUnit(const unit_info perso) const;
    Unit_sptr getUnit(const perso_info perso) const;

    size_t getPlayerCount();
    std::vector<int> getScores() const;

    int getCurrentTurn() const;
    void incrementTurn();

    void reserveMoves(size_t n);
    void addMoves(size_t n, std::pair<position, Unit_sptr> movement);

private:
    // The map
    Map* map_;
    rules::PlayerVector_sptr players_;
    UnitList units_;
    std::vector<palantir> palantiri_;

    std::vector<std::vector<std::pair<position, Unit_sptr>>> pendingMoves_;

    // TODO increment each turn
    int current_turn_;
};

#endif // !GAME_HH_
