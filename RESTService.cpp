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
#include "api/FunsResource.h"

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

	auto p = [ & ] (auto path, unique_ptr<FunsResourceImpl> impl)
	{
		service->publish(make_shared<FunsResource>(path, std::move(impl), db, auth_manager));
	};
	p(resources::schedules, make_unique<SchedulesImpl>());
	p(resources::schedules_id, make_unique<SchedulesIDImpl>());
	p(resources::schedules_odd, make_unique<SchedulesOddImpl>());
	p(resources::schedules_even, make_unique<SchedulesEvenImpl>());
	p(resources::schedules_unusual, make_unique<SchedulesUnusualImpl>());
	p(resources::schedules_subjects, make_unique<SchedulesSubjectsImpl>());
	p(resources::users, make_unique<UsersImpl>());
	p(resources::users_id, make_unique<UsersIDImpl>());

}

void RESTService::start()
{
	service->start(settings);
}

