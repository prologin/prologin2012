#include <iostream>

#include <net/client-messenger.hh>

//static net::ClientMessenger_sptr client_msgr;

extern "C" void client_setup(net::ClientMessenger_sptr client_msgr_)
{
    //client_msgr = client_msgr_;

    std::cout << "Prologin 2012 Client Setup" << std::endl;
}

extern "C" bool client_turn()
{
    std::cout << "Prologin 2012 Client Turn" << std::endl;
}

extern "C" void client_teardown()
{
    std::cout << "Prologin 2012 Client Teardown" << std::endl;
}
