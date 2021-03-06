#include "RESTService.h"
#include <csignal>


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
#include "api/Auth.h"

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
	p(resources::auth, make_unique<AuthImpl>());

	service->set_ready_handler([](Service & s)
	{
		utility::log()->info("Service is ready.");
	});

	service->set_signal_handler(SIGINT, [ & ](const int s)
	{
		utility::log()->alert("SIGINT recived!");
		utility::log()->flush();
		exit(EXIT_SUCCESS);
	});

	service->set_error_handler([](const int, const exception& e, const shared_ptr<Session> session)
	{
		constexpr auto error_str = "Internal Server Error ";
		if (session->is_open())
			session->close(INTERNAL_SERVER_ERROR, error_str);
		utility::log()->error() << error_str << e.what();
	});
	
}

void RESTService::start()
{
	service->start(settings);
}