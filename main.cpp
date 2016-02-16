#include <iostream>
#include <cpprest/uri.h>
#include "FunsServer.h"

std::unique_ptr<FunsServer> g_server;

void on_initialize(const string_t& address)
{
    // Build our listener's URI from the configured address and the hard-coded path "blackjack/dealer"

    uri_builder uri(address);
    uri.append_path(U("api"));

    auto addr = uri.to_uri().to_string();
    g_server = std::unique_ptr<FunsServer>(new FunsServer(addr));
    g_server->open().wait();

    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
}

void on_shutdown()
{
    g_server->close().wait();
}

int main()
{
    std::cout << "FUNS-server\nVersion " << 1 << "." << 0 << std::endl;

    utility::string_t port = U("34666");

    utility::string_t address = U("http://localhost:");
    address.append(port);

    on_initialize(address);
    std::string line;
    std::cout << "Press ENTER to exit." << std::endl;
    std::getline(std::cin, line);
    on_shutdown();

    return 0;
}

