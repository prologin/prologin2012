#ifndef GAME_HH_
# define GAME_HH_

# include <vector>

# include <rules/game-state.hh>
# include <rules/player.hh>

# include "unit.hh"
# include "ability.hh"

enum game_phase {
    PHASE_PLACEMENT,
    PHASE_DEPLACEMENT,
    PHASE_ATTAQUE,
};


class Map;

class GameState : public rules::GameState
{
public:
    GameState(Map* map, rules::Players_sptr players);

    virtual rules::GameState* copy() const;

    ~GameState();

    void init();

    Map* getMap() const;

    palantir_t getPalantir(int player_id) const;
    void setPalantir(int player_id, position target);

    UnitList getUnits() const;
    Unit_sptr getUnit(const unit_info perso) const;
    Unit_sptr getUnit(const perso_info perso) const;

    size_t getPlayerCount();
    std::vector<int> getScores() const;

    int getCurrentTurn() const;
    void incrementTurn();

    game_phase getPhase() const;
    /*
     * @return true when the game is finished
     */
    bool isFinished();

    std::vector<std::vector<std::pair<position, Unit_sptr>>>& getPendingMoves();

private:
    // The map
    Map* map_;
    rules::Players_sptr players_;
    UnitList units_;
    std::vector<palantir_t> palantiri_;

    std::vector<std::vector<std::pair<position, Unit_sptr>>> pendingMoves_;

    // TODO increment each turn
    int current_turn_;
};

#endif // !GAME_HH_
