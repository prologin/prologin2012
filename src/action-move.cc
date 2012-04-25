#include "action-move.hh"

#include "constant.hh"

ActionMove::ActionMove()
    : unit_(),
      path_(),
      direction_(ORIENTATION_NORD),
      player_(-1),
      id_(ACTION_MOVE)
{
}

ActionMove::ActionMove(perso_info unit, std::vector<position>& path,
            orientation& direction, int player)
    : rules::Action<GameState>(),
      unit_(unit),
      path_(path),
      direction_(direction),
      player_(player),
      id_(ACTION_MOVE)
{
}

int ActionMove::check(const GameState*) const
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
  gameState->getPendingMoves().reserve(path_.size());

  for (size_t i = 0; i < path_.size(); ++i)
    gameState->getPendingMoves()[i].push_back(std::make_pair(path_[i],
          gameState->getUnit(unit_)));
}
