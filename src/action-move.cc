#include "action-move.hh"

#include "constant.hh"
#include "map.hh"
#include "cell.hh"

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

int ActionMove::check(const GameState* st) const
{
    DEBUG("ActionMove::check");

    Unit_sptr unit = st->getUnit(unit_);

    int move_points = unit->getMovementPoints();

    position current_unit_position = unit->getPosition();

    for (auto pos : path_)
    {
        if (abs(current_unit_position.x - pos.x)
                + abs(current_unit_position.y - pos.y) != 1)
            return CHEMIN_IMPOSSIBLE;

        current_unit_position = pos;
        move_points -= st->getMap()->getCell(pos)->getCost();

        if (move_points < 0)
            return CHEMIN_IMPOSSIBLE;
    }

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
    auto& pendingMoves = gameState->getPendingMoves();

    for (size_t i = 0; i < path_.size(); ++i)
    {
        if (i < pendingMoves.size())
            pendingMoves[i].push_back(std::make_pair(path_[i], gameState->getUnit(unit_)));
        else
            pendingMoves.push_back(std::vector<std::pair<position, Unit_sptr>>(1,
                        std::make_pair(path_[i], gameState->getUnit(unit_))));
    }
}
