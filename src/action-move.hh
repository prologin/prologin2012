#ifndef ACTION_MOVE_HH_
# define ACTION_MOVE_HH_

# include <rules/action.hh>

# include "constant.hh"
# include "game.hh"
# include "unit.hh"

class ActionMove : public rules::Action<GameState>
{
public:
    ActionMove(perso_info unit, std::vector<position>& path,
            orientation& direction, int player);

    ActionMove();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);

    uint32_t player_id() const
        { return player_; }
    uint32_t id() const
        { return id_; }
    perso_info getPersoInfo() const
        { return unit_; }

    void applyDirection(GameState* st) const;

protected:
    virtual void apply_on(GameState* st) const;

protected:
    perso_info unit_;
    int path_length_;
    std::vector<position> path_;
    orientation direction_;

    int player_;
    int id_;
};

#endif // !ACTION_MOVE_HH_
