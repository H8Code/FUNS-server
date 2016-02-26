#include "RESTService.h"


#include "FunsConfig.h"
#include "api/Schedules.h"
#include "api/SchedulesID.h"
#include "api/Users.h"
#include "api/UsersID.h"
#include "api/SchedulesOdd.h"
#include "api/SchedulesEven.h"
#include "api/SchedulesUnusual.h"
#include "api/SchedulesSubjects.h"

using namespace funs;
using namespace restbed;
using namespace std;

RESTService::RESTService(shared_ptr<DBDriver> _db) :
db{_db},
settings{make_shared<Settings>()},
service{make_shared<Service>()},
auth_manager{make_shared<AuthManager>(_db)}
{
	settings->set_port(config::port);
	settings->set_bind_address(config::bind_addres);
	settings->set_default_header("Connection", "close");
	settings->set_worker_limit(config::worker_limit);

	db->remove_token("mom", "WIDI2P7S3DEDBKY4Y320C8OQEUKONPWF");
	
	service->publish(make_shared<APISchedules>(db, resources::schedules, auth_manager));
	service->publish(make_shared<APISchedulesID>(db, resources::schedules_id));
	service->publish(make_shared<APIUsers>(db, resources::users));
	service->publish(make_shared<APIUsersID>(db, resources::users_id));
	service->publish(make_shared<APISchedulesOdd>(db, resources::schedules_odd));
	service->publish(make_shared<APISchedulesEven>(db, resources::schedules_even));
	service->publish(make_shared<APISchedulesUnusual>(db, resources::schedules_unusual));
	service->publish(make_shared<APISchedulesSubjects>(db, resources::schedules_subjects));
}

void RESTService::start()
{
	service->start(settings);
}

