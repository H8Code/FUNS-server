#include <iostream>
#include <bits/c++config.h>

#include "AuthManager.h"
#include "FunsConfig.h"

using namespace funs;
using namespace std;
using namespace restbed;

bool AuthManager::allow(request_t request, const shared_ptr<Session> &session, const string &user) const
{
	bool answer = false;
	const auto token = session->get_request()->get_header(config::token_header, "<NONE>");

	switch (request) {
	case AuthManager::request_t::POST:
		answer = db->is_token_exist(user, token);
		break;
	default:
		break;
	}
	if (not answer) {
		auto body = session->get_request()->get_body();
		utility::log()->warn()
			<< "BAD AUTH! Token: "
			<< token
			<< " User: "
			<< user
			<< " Path: "
			<< session->get_request()->get_path()
			<< " Body: "
			<< string
			{
				body.begin(), body.end()
			}
		<< " Destination: "
		<< session->get_destination();
	}
	return answer;
}

const string AuthManager::login(const string &user, const string & password)
{
	string hash, salt;
	if (db->get_password_hash_and_salt(user, hash, salt)) {
		if (hash == utility::hash(salt + password)) {
			auto token = utility::random_string(config::token_lenght);
			db->save_token(user, token);
			return token;
		} else {
			throw invalid_argument("Bad password for " + user);
		}

	} else {
		throw invalid_argument("User " + user + " is not exist");
	}
}

const void AuthManager::logout(const string& user, const string & token)
{

}