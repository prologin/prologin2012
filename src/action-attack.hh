#ifndef ACTION_ATTACK_HH_
# define ACTION_ATTACK_HH_

# include <map>

# include <rules/action.hh>

# include "constant.hh"
# include "game.hh"
# include "unit.hh"

class ActionAttack : public rules::Action<GameState>
{
public:
    ActionAttack(perso_info unit, attaque_type atk, position target,
            int player);

    ActionAttack();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);

    uint32_t player_id() const
        { return player_; }
    uint32_t id() const
        { return id_; }

    attaque_type getType() const;
    void markFusRoDah(GameState* gameState, std::map<int, int>& markedUnits) const;
    void applyAttack(GameState* gameState) const;

protected:
    virtual void apply_on(GameState* gameState) const;

protected:
    perso_info unit_;
    attaque_type atk_id_;
    position target_;

    int player_;
    int id_;
};


#endif // !ACTION_ATTACK_HH_
