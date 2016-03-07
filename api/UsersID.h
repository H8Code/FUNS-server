#ifndef USERSID_H
#define USERSID_H

#include "FunsResourceImpl.h"

class UsersIDImpl
: public FunsResourceImpl {
public:

	void get_handler(const shared_ptr<Session> &session) override
	{
		const auto id = session->get_request()->get_path_parameter("id", true);
		auto data = db->get_users_by_id(id);
		session->close(OK, data);
	}
};

#endif /* USERSID_H */

