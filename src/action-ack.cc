#include "action-ack.hh"

ActionAck::ActionAck(int player) : player_(player), id_(ACTION_ACK) {}

ActionAck::ActionAck() : player_(-1), id_(ACTION_ACK) {}

void ActionAck::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_);
}
