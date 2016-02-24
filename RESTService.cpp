#include "RESTService.h"

RESTService::RESTService(shared_ptr<DBDriver> _db):
    db{_db},
    settings{make_shared<Settings>()},
    service{make_shared<Service>()}
{
    settings->set_port(funs_config::port);
    settings->set_bind_address(funs_config::bind_addres);
    settings->set_default_header( "Connection", "close" );
    settings->set_worker_limit(funs_config::worker_limit);

    service->publish(make_shared<APISchedules>(db, resources::schedules));
    service->publish(make_shared<APISchedulesID>(db, resources::schedules_id));
    service->publish(make_shared<APIUsers>(db, resources::users));
}

void RESTService::start()
{
    service->start(settings);
}

