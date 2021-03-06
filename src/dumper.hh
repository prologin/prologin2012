#ifndef DUMPER_HH_
#define DUMPER_HH_

#include <rules/actions.hh>

#include "game.hh"

const char* dump_game_state(const GameState& st, rules::Actions& acts);

#endif // !DUMPER_HH_
