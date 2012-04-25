#include "action-attack.hh"

#include "constant.hh"

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

void ActionAttack::apply_on(GameState*) const
{
    // TODO
}
