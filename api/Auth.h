#ifndef AUTH_H
#define AUTH_H

#include "FunsResourceImpl.h"
#include "../Utility.h"

using namespace restbed;
using namespace std;
using namespace funs;

class AuthImpl :
public FunsResourceImpl {

	void post_handler(const std::shared_ptr<restbed::Session> &session) override
	{
		const auto request = session->get_request();

		size_t content_length{0};
		request->get_header("Content-Length", content_length);

		session->fetch(content_length,
			[ = ](const shared_ptr<Session> session, const Bytes & body){

			const string user = funs::utility::field_from_JSON_bytes(body, "login");
			const string password = funs::utility::field_from_JSON_bytes(body, "password");

			try {
				auto token = auth->login(user, password);
				session->close(OK, utility::token_to_JSON(token));
			} catch (logic_error &e) {
				session->close(FORBIDDEN);
				utility::log()->warn() << e.what();
			}
		});

	}
};

#endif /* AUTH_H */

