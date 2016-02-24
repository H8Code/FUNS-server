#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <memory>
#include <restbed>
#include <random>

#include "DBDriver.h"

#include <iostream>
using namespace restbed;
using namespace std;

class AuthManager {
public:

	enum request_t : uint_fast8_t {
		GET = 1,
		POST = 2
	};

	AuthManager(shared_ptr<DBDriver> _db)
	: db{_db}
	{
		cout << "AM create" << endl;
	}

	bool allow(request_t request, const shared_ptr<Session> session, const string &user) const;

	const string login(const string &user, const string &password);
	const void logout(const string &user, const string &token);

private:
	shared_ptr<DBDriver> db;

	static const string gen_token();
};

#endif /* AUTHMANAGER_H */

