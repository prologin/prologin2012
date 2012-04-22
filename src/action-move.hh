#ifndef ACTION_MOVE_HH_
# define ACTION_MOVE_HH_

# include <rules/action.hh>

# include "constant.hh"
# include "game.hh"
# include "unit.hh"

class ActionMove : public rules::Action<GameState>
{
public:
    ActionMove(perso_info unit, std::vector<orientation>& path,
            orientation& direction)
        : rules::Action<GameState>(), unit_(unit), path_(path),
        direction_(direction_)
    {}

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);

protected:
    virtual void apply_on(GameState* st) const;

    perso_info unit_;
    std::vector<orientation> path_;
    orientation direction_;
};

#endif // !ACTION_MOVE_HH_
