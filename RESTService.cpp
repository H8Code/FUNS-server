#include "RESTService.h"

#include "api/Schedules.h"
#include "api/SchedulesID.h"
#include "api/Users.h"
#include "api/UsersID.h"

RESTService::RESTService(shared_ptr<DBDriver> _db) :
db{_db},
settings{make_shared<Settings>()},
service{make_shared<Service>()},
auth_manager{make_shared<AuthManager>(_db)}
{
	settings->set_port(funs_config::port);
	settings->set_bind_address(funs_config::bind_addres);
	settings->set_default_header("Connection", "close");
	settings->set_worker_limit(funs_config::worker_limit);

	db->remove_token("mom", "WIDI2P7S3DEDBKY4Y320C8OQEUKONPWF");
	
	service->publish(make_shared<APISchedules>(db, resources::schedules, auth_manager));
	service->publish(make_shared<APISchedulesID>(db, resources::schedules_id));
	service->publish(make_shared<APIUsers>(db, resources::users));
	service->publish(make_shared<APIUsersID>(db, resources::users_id));
}

void RESTService::start()
{
	service->start(settings);
}

