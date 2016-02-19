#include "RESTService.h"

RESTService::RESTService(shared_ptr<DBDriver> db):
    db{db},
    settings{make_shared<Settings>()},
    service{make_shared<Service>()}
{
    settings->set_port(funs_config::port);
    settings->set_bind_address(funs_config::bind_addres);
    settings->set_default_header( "Connection", "close" );
    settings->set_worker_limit(funs_config::worker_limit);

    service->publish(make_shared<APISchedules>(db));
}

void RESTService::start()
{
    service->start(settings);
}

