#ifndef FUNSRESOURCEIMPL_H
#define FUNSRESOURCEIMPL_H

#include <memory>
#include <restbed>
#include "../DBDriver.h"
#include "../AuthManager.h"

class FunsResourceImpl {
public:
	FunsResourceImpl() = default;

	virtual void get_handler(const std::shared_ptr<restbed::Session> session)
	{
		session->close(restbed::NOT_IMPLEMENTED);
	}

	virtual void post_handler(const std::shared_ptr<restbed::Session> session)
	{
		session->close(restbed::NOT_IMPLEMENTED);
	}

	virtual void delete_handler(const std::shared_ptr<restbed::Session> session)
	{
		session->close(restbed::NOT_IMPLEMENTED);
	}

	void init(std::shared_ptr<DBDriver> db_, std::shared_ptr<AuthManager> auth_)
	{
		auth = auth_;
		db = db_;
	}

protected:
	std::shared_ptr<AuthManager> auth;
	std::shared_ptr<DBDriver> db;
};

#endif /* FUNSRESOURCEIMPL_H */

