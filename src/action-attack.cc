#include "map.hh"
#include "action-attack.hh"

#include "constant.hh"

ActionAttack::ActionAttack()
    : unit_(),
      atk_id_(ATTAQUE_NORMALE),
      target_({0, 0}),
      player_(-1),
      id_(ACTION_ATTACK)
{
}

ActionAttack::ActionAttack(perso_info unit, attaque_type atk, position target,
        int)
    : unit_(unit),
      atk_id_(atk),
      target_(target),
      id_(ACTION_ATTACK)
{
}

int ActionAttack::check(const GameState*) const
{
    DEBUG("ActionAttack::check");
    // TODO

    return OK;
}

void ActionAttack::handle_buffer(utils::Buffer& buf)
{
    buf.handle(unit_);
    buf.handle(atk_id_);
    buf.handle(target_);
}

attaque_type ActionAttack::getType() const
{
  return atk_id_;
}

void ActionAttack::markFusRohDah(GameState* gameState, std::map<int, int>& markedUnits) const
{
  auto unit = gameState->getUnit(unit_);
  auto unitsPosition = gameState->getMap()->getSurroundings(unit->getPosition(),
      unit->getOrientation(), unit->getVision());

  for (auto unitPosition : unitsPosition)
  {
    for (auto unitInfo : gameState->getMap()->getCell(unitPosition)->getUnits())
    {
      int unitInfoId = unitInfo.player_id * 10 + unitInfo.classe;
      auto it = markedUnits.find(unitInfoId);
      if (it != markedUnits.end())
      {
        gameState->getUnit(unitInfo)->attacked(9001, unit_info { unit_.equipe, unit_.classe });
        gameState->getUnit(unitInfo)->attacked(9001,
            unit_info { it->second / 10, (perso_classe)(it->second % 10)});
      }
      else
        markedUnits.insert(std::make_pair(unitInfoId, unit_.equipe * 10 + unit_.classe));
    }
  }
}

void ActionAttack::applyAttack(GameState *gameState) const
{
  switch (atk_id_)
  {
    case ATTAQUE_NORMALE:
      if (unit_.classe == PERSO_BARBARE)
        applyBarbareAttack(gameState);
      else if (unit_.classe == PERSO_VOLEUR)
        applySimpleAttack(gameState, VOLEUR_ATTAQUE, true);
      else
        applySimpleAttack(gameState, ELFE_ATTAQUE, true);
      break;
    case ATTAQUE_PALANTIR:
      gameState->setPalantir(player_, target_);
      break;
    case ATTAQUE_TRAITRISE:
      applySimpleAttack(gameState, 9001, false);
      break;
    case ATTAQUE_FUS_RO_DAH:
      applyFusRohDah(gameState);
      break;
    case ATTAQUE_I_SEE:
      //FIXME: NOT A PALANTIR
      gameState->setPalantir(player_, target_);
      break;
    case ATTAQUE_LOTO:
      applySimpleAttack(gameState, ELFE_ATTAQUE, true);
      break;
    default:
      break;
  }
}

void ActionAttack::apply_on(GameState* gameState) const
{
  if (atk_id_ == ATTAQUE_FUS_RO_DAH)
    gameState->getPendingAttacks().push_front(this);
  else
    gameState->getPendingAttacks().push_back(this);
}

void ActionAttack::applySimpleAttack(GameState* gameState, int power, bool friendlyFire) const
{
  Cell* target = gameState->getMap()->getCell(target_);

  for (auto unitInfo : target->getUnits())
  {
    auto unit = gameState->getUnit(unitInfo);

    if (!friendlyFire && unit->getPlayer() == player_)
      continue;
    unit->attacked(power, unit_info { unit_.equipe, unit_.classe });
  }
}

void ActionAttack::applyBarbareAttack(GameState* gameState) const
{
  position center = target_;
  applySimpleAttack(gameState, BARBARE_ATTAQUE, true);

  ActionAttack* action = const_cast<ActionAttack*> (this);
  action->target_ = { center.x + 1, center.y };
  if (gameState->getMap()->isPositionValid(action->target_))
    action->applySimpleAttack(gameState, BARBARE_ATTAQUE, true);
  action->target_ = { center.x - 1, center.y };
  if (gameState->getMap()->isPositionValid(action->target_))
    action->applySimpleAttack(gameState, BARBARE_ATTAQUE, true);
  action->target_ = { center.x, center.y + 1};
  if (gameState->getMap()->isPositionValid(action->target_))
    applySimpleAttack(gameState, BARBARE_ATTAQUE, true);
  action->target_ = { center.x, center.y - 1};
  if (gameState->getMap()->isPositionValid(action->target_))
    action->applySimpleAttack(gameState, BARBARE_ATTAQUE, true);

  action->target_ = center;
}

void ActionAttack::applyFusRohDah(GameState* gameState) const
{
  auto unit = gameState->getUnit(unit_);
  position ownPosition = unit->getPosition();
  orientation dir = unit->getOrientation();
  int vision = unit->getVision();
  auto unitsPosition = gameState->getMap()->getSurroundings(ownPosition, dir, vision);

  for (auto unitPosition : unitsPosition)
  {
    position newPosition = unitPosition;
    int North = (dir == ORIENTATION_SUD) - (dir == ORIENTATION_NORD);
    int East = (dir == ORIENTATION_EST) - (dir == ORIENTATION_OUEST);
    int maxDistance = unit->getVision() - abs((unitPosition.x - ownPosition.x) * East)
      + abs((unitPosition.y - ownPosition.y) * North);

    for (int i = 0; i < maxDistance; ++i)
    {
      newPosition = { newPosition.x + East, newPosition.y + North };
      if (gameState->getMap()->isPositionValid(newPosition) &&
          gameState->getMap()->getCell(newPosition)->getType() != ZONE_MUR)
        continue;
      newPosition = { newPosition.x - East, newPosition.y - North };
      break;
    }

    for (auto unitInfo : gameState->getMap()->getCell(unitPosition)->getUnits())
    {
      gameState->getUnit(unitInfo)->setPosition(newPosition);
      gameState->getMap()->moveUnit(unitInfo, unitPosition, newPosition);
    }
  }
}
