#ifndef USERS_H
#define USERS_H

#include "FunsResourceImpl.h"

class UsersImpl
: public FunsResourceImpl {
public:

	void get_handler(const shared_ptr<Session> session) override
	{
		auto data = db->get_users();
		session->close(OK, data);
	}
};


#endif /* USERS_H */

