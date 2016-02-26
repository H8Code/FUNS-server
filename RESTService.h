#ifndef SERVICE_H
#define SERVICE_H

#include <memory>
#include <restbed>
#include "FunsConfig.h"
#include "DBDriver.h"
#include "AuthManager.h"

using namespace restbed;
using namespace std;

namespace resources {
	constexpr auto schedules = "/api/schedules";
	constexpr auto schedules_id = "/api/schedules/{id: .*}";
	constexpr auto users = "/api/users";
	constexpr auto users_id = "/api/users/{id: .*}";
	constexpr auto schedules_odd = "/api/schedules/{id: .*}/odd";
}

class RESTService {
public:
	RESTService() = delete;
	RESTService(shared_ptr<DBDriver> db);

	void start();

private:
	shared_ptr<DBDriver> db;
	shared_ptr<Settings> settings;
	shared_ptr<Service> service;
	shared_ptr<AuthManager> auth_manager;
};

#endif // SERVICE_H
