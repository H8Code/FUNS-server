#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <memory>
#include <restbed>
#include <random>

#include "DBDriver.h"
#include "Utility.h"
#include "FunsConfig.h"


class AuthManager {
public:
	enum request_t : uint_fast8_t {
		GET = 1,
		POST = 2
	};

	AuthManager() = delete;
	explicit AuthManager(std::shared_ptr<DBDriver> _db)
	: db{_db}
	{
	}

	bool allow(request_t request, const std::shared_ptr<restbed::Session> session, const std::string &user) const;

	const std::string login(const std::string &user, const std::string &password);
	const void logout(const std::string &user, const std::string &token);

private:
	std::shared_ptr<DBDriver> db;
};

#endif /* AUTHMANAGER_H */

