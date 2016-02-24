#ifndef SCHEDULES
#define SCHEDULES

#include <restbed>
#include <memory>
#include "../DBDriver.h"
#include "FunsResource.h"

#include <iostream>
#include <sstream>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>

using namespace restbed;
using namespace std;

class APISchedules
: public FunsResource {
public:

	APISchedules(shared_ptr<DBDriver> db, const string &path, shared_ptr<AuthManager> auth)
	: FunsResource(db, path, auth)
	{
	}
private:

	void get_handler(const shared_ptr<Session> session) override
	{
		auto data = db->get_schedules();
		session->close(OK, data);
	}

	void post_handler(const shared_ptr<Session> session) override
	{
		std::cout << "POST" << std::endl;

		const auto request = session->get_request();

		size_t content_length{0};
		request->get_header("Content-Length", content_length);

		session->fetch(content_length,
			[ = ](const shared_ptr<Session> session, const Bytes & body){

			auto name = __get_field_from_bytes(body, "creator");

			if (auth->allow(AuthManager::request_t::POST, session, name))
				session->close(OK);
			else
				session->close(FORBIDDEN);
			});
	}

};

#endif // SCHEDULES

