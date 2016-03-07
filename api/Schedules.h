#ifndef SCHEDULES
#define SCHEDULES

#include "../Utility.h"
#include "FunsResourceImpl.h"

using namespace restbed;
using namespace std;

class SchedulesImpl
: public FunsResourceImpl {
public:

	void get_handler(const shared_ptr<Session> &session) override
	{
		auto data = db->get_schedules();
		session->close(OK, data);
	}

	void post_handler(const shared_ptr<Session> &session) override
	{
		const auto request = session->get_request();

		size_t content_length{0};
		request->get_header("Content-Length", content_length);

		session->fetch(content_length,
			[ = ](const shared_ptr<Session> session, const Bytes &body){

			const string name = funs::utility::field_from_JSON_bytes(body, "creator");

			if (auth->allow(AuthManager::request_t::POST, session, name))
				session->close(OK);
			else
				session->close(FORBIDDEN);
			});
	}

};

#endif // SCHEDULES

