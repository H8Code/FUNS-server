#ifndef SERVICE_H
#define SERVICE_H

#include <memory>
#include <restbed>

#include "DBDriver.h"
#include "AuthManager.h"

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
	RESTService(std::shared_ptr<DBDriver> db);

	void start();

private:
	std::shared_ptr<DBDriver> db;
	std::shared_ptr<restbed::Settings> settings;
	std::shared_ptr<restbed::Service> service;
	std::shared_ptr<AuthManager> auth_manager;
};

#endif // SERVICE_H
