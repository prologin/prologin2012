#include "action-move.hh"

#include "constant.hh"

ActionMove::ActionMove(perso_info unit, std::vector<position>& path,
            orientation& direction, int player)
    : rules::Action<GameState>(),
      unit_(unit),
      path_(path),
      direction_(direction_),
      player_(player),
      id_(ACTION_MOVE)
{
}

int ActionMove::check(const GameState* st) const
{
    DEBUG("ActionMove::check");

    CHECK(player_ >= 0);

    return OK;
}

void ActionMove::handle_buffer(utils::Buffer& buf)
{
    buf.handle(unit_);
    buf.handle(path_);
    buf.handle(direction_);
}

void ActionMove::apply_on(GameState* gameState) const
{
  gameState->reserveMoves(path_.size());

  for (size_t i = 0; i < path_.size(); ++i)
    gameState->addMoves(i, std::make_pair(path_[i],
          gameState->getUnit(unit_)));
}
