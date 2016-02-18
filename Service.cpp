#include "Service.h"

FUNSService::FUNSService(shared_ptr<DBDriver> db):
    db{db},
    settings{make_shared<Settings>()},
    service{make_shared<Service>()}
{
    settings->set_port(FUNS::port);
    settings->set_bind_address(FUNS::bind_addres);
    settings->set_default_header( "Connection", "close" );
    settings->set_worker_limit(FUNS::worker_limit);

    service->publish(make_shared<RSchedules>(db));
}

void FUNSService::start()
{
    service->start(settings);
}

