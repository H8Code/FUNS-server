#include "FunsServer.h"

FunsServer::FunsServer()
{

}

FunsServer::FunsServer(string_t url):
    m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&FunsServer::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&FunsServer::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&FunsServer::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&FunsServer::handle_delete, this, std::placeholders::_1));
}

void FunsServer::handle_get(http_request message)
{
    ucout << message.to_string() << std::endl;
    message.reply(status_codes::OK, "kek");
}

void FunsServer::handle_put(http_request message)
{
    ucout << message.to_string() << std::endl;
    message.reply(status_codes::NotFound);
}

void FunsServer::handle_post(http_request message)
{
    ucout << message.to_string() << std::endl;
    message.reply(status_codes::NotFound).wait();
    _exit(666);
}

void FunsServer::handle_delete(http_request message)
{
    ucout << message.to_string() << std::endl;
    message.reply(status_codes::NotFound);
}

