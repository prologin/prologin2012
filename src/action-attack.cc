#include "action-attack.hh"
#include "ability.hh"

#include "constant.hh"
#include "map.hh"
#include "cell.hh"

ActionAttack::ActionAttack()
    : unit_(),
      atk_id_(ATTAQUE_NORMALE),
      target_({0, 0}),
      player_(-1),
      id_(ACTION_ATTACK)
{
}

ActionAttack::ActionAttack(perso_info unit, attaque_type atk, position target, int)
    : unit_(unit),
      atk_id_(atk),
      target_(target),
      id_(ACTION_ATTACK)
{
}

int ActionAttack::check(const GameState* gameState) const
{
    DEBUG("ActionAttack::check");

    Unit_sptr unit = gameState->getUnit(unit_);
    Ability* ability = unit->getAbility(atk_id_);

    if (!ability)
        return ATTAQUE_INDISPONIBLE;

    unit_info info = { unit_.equipe, unit_.classe };
    position target = { target_.x, target_.y };

    return ability->check(*gameState, info, target);
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

void ActionAttack::markFusRoDah(GameState* gameState, std::map<int, int>& markedUnits) const
{
    Map* map = gameState->getMap();
    auto attacker = gameState->getUnit(unit_);
    auto unitsPositions = map->getSurroundings(attacker->getPosition(),
            attacker->getOrientation(), attacker->getVision());

    for (auto unitsPosition : unitsPositions)
    {
        for (auto victimInfo : map->getCell(unitsPosition)->getUnits())
        {
            int victimId= victimInfo.player_id * 10 + victimInfo.classe;
            int attackerId = unit_.equipe * 10 + unit_.classe;
            unit_info attackerInfo = { unit_.equipe, unit_.classe };

            auto searchVictim = markedUnits.find(victimId);
            if (searchVictim != markedUnits.end())
            {
                unit_info otherInfo =
                {
                    searchVictim->second / 10,
                    (perso_classe)(searchVictim->second % 10)
                };
                gameState->getUnit(victimInfo)->attacked(255, attackerInfo);
                gameState->getUnit(victimInfo)->attacked(255, otherInfo);
            }
            else
                markedUnits.insert(std::make_pair(victimId, attackerId));
        }
    }
}

void ActionAttack::applyAttack(GameState *gameState) const
{
    Ability* attack = gameState->getUnit(unit_)->getAbility(atk_id_);

    unit_info info = { unit_.equipe, unit_.classe };
    position target = { target_.x, target_.y };

    attack->apply(gameState, info, target);
}

void ActionAttack::apply_on(GameState* gameState) const
{
    auto& pendingAttacks = gameState->getPendingAttacks();
    if (atk_id_ == ATTAQUE_FUS_RO_DAH)
        pendingAttacks.push_front(this);
    else
        pendingAttacks.push_back(this);
}
