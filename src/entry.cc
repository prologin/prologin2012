/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2012 Prologin
*/

#include <cstdlib>
#include <rules/client-messenger.hh>
#include <rules/config.hh>
#include <rules/options.hh>
#include <rules/server-messenger.hh>
#include <utils/log.hh>

#include "rules.hh"

static Rules* rules_;

extern "C" {

void rules_config(rules::Config* cfg)
{
    cfg->name = "prologin2012";
    cfg->player_count = 2;
}

void rules_init(const rules::Options& opt)
{
    utils::Logger::get().level() = (utils::Logger::DisplayLevel)opt.verbose;

    rules_ = new Rules(opt);
}

void rules_result()
{
    delete rules_;
}

void player_loop(rules::ClientMessenger_sptr msgr)
{
    rules_->player_loop(msgr);
}

void spectator_loop(rules::ClientMessenger_sptr msgr)
{
    rules_->spectator_loop(msgr);
}

void server_loop(rules::ServerMessenger_sptr msgr)
{
    rules_->server_loop(msgr);
}

} // extern "C"
