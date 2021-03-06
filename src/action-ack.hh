#ifndef ACTION_ACK_HH_

#define ACTION_ACK_HH_

#include <rules/action.hh>

#include "constant.hh"
#include "game.hh"
#include "unit.hh"

class ActionAck : public rules::Action<GameState>
{
public:
    ActionAck(int player);

    ActionAck();

    int check(const GameState&) const { return 0; }
    void handle_buffer(utils::Buffer&);

    uint32_t player_id() const { return player_; }
    uint32_t id() const { return id_; }

protected:
    virtual void apply_on(GameState*) const {}

protected:
    int player_;
    int id_;
};

#endif /* !ACTION_ACK_HH_ */
