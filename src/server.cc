#include <iostream>

#include <net/server-messenger.hh>

//static net::ServerMessenger_sptr server_msgr;

extern "C" void server_setup(net::ServerMessenger_sptr server_msgr_)
{
    //server_msgr = server_msgr_;

    std::cout << "Prologin 2012 Server Setup" << std::endl;
}

extern "C" bool server_turn()
{
    std::cout << "Prologin 2012 Server Turn" << std::endl;
}

extern "C" void server_teardown()
{
    std::cout << "Prologin 2012 Server Teardown" << std::endl;
}
