#include "action-move.hh"

#include "constant.hh"

int ActionMove::check(const GameState* st) const
{
    return OK;
}

void ActionMove::handle_buffer(utils::Buffer& buf)
{
    buf.handle(unit_);
    buf.handle(path_);
    buf.handle(direction_);
}

void ActionMove::apply_on(GameState*) const
{}
