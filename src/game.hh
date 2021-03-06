#ifndef GAME_HH_
#define GAME_HH_

#include <list>
#include <vector>

#include <rules/game-state.hh>
#include <rules/player.hh>

#include "ability.hh"
#include "unit.hh"

enum game_phase
{
    PHASE_PLACEMENT,
    PHASE_DEPLACEMENT,
    PHASE_ATTAQUE,
};

enum action_id
{
    ACTION_MOVE = 0,
    ACTION_ATTACK = 1,
    ACTION_ACK = 2
};

typedef struct remote_vision
{
    bool palantir_activated;
    position palantir_location;

    bool elfe_vision_activated;
    position elfe_vision_location;

} remote_vision;

class Map;
class ActionAttack;
class ActionMove;

class GameState : public rules::GameState
{
public:
    GameState(Map* map, const rules::Players& players);
    GameState* copy() const;

    ~GameState();

    void init();

    Map* getMap() const;

    bool isPalantirActivated(int player_id) const;
    position getPalantir(int player_id) const;
    void setPalantir(int player_id, position target);

    bool isElfeVisionActivated(int player_id) const;
    position getElfeVision(int player_id) const;
    void setElfeVision(int player_id, position target);
    void deactivateElfeVision(int player_id);

    Units getUnits() const;
    Unit_sptr getUnit(const unit_info perso) const;
    Unit_sptr getUnit(const perso_info perso) const;

    size_t getPlayerCount() const;
    std::vector<int> getScores() const;

    int getCurrentTurn() const;
    void incrementTurn();

    void setPhase(game_phase phase);
    game_phase getPhase() const;
    /*
     * @return true when the game is finished
     */
    bool isFinished();

    std::vector<std::vector<std::pair<position, const ActionMove*>>>&
    getPendingMoves();
    std::list<const ActionAttack*>& getPendingBastoooon();
    std::list<const ActionAttack*>& getPendingAttacks();

private:
    GameState(const GameState& st);

    // The map
    Map* map_;
    rules::Players players_;
    Units units_;
    std::vector<remote_vision> remote_vision_;

    std::vector<std::vector<std::pair<position, const ActionMove*>>>
        pendingMoves_;
    std::list<const ActionAttack*> pendingAttacks_;
    std::list<const ActionAttack*> pendingBastoooon_;

    game_phase game_phase_;
    int current_turn_;
};

#endif // !GAME_HH_
