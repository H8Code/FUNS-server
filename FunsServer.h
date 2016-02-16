#ifndef FUNSSERVER_H
#define FUNSSERVER_H

#include <cpprest/http_listener.h>              // HTTP server</span>
#include <cpprest/json.h>                       // JSON library</span>


using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace http;                  // Common HTTP functionality
using namespace experimental::listener;          // HTTP server
using namespace json;                                  // JSON library

class FunsServer
{
public:
	FunsServer();
        FunsServer(string_t url);
        pplx::task<void> open() { return m_listener.open(); }
        pplx::task<void> close() { return m_listener.close(); }

private:
        void handle_get(http_request message);
        void handle_put(http_request message);
        void handle_post(http_request message);
        void handle_delete(http_request message);

        http_listener m_listener;
};

#endif // FUNSSERVER_H
