#include <iostream>
#include <bits/c++config.h>

#include "AuthManager.h"
#include "FunsConfig.h"

using namespace funs;
using namespace std;
using namespace restbed;

bool AuthManager::allow(request_t request, const shared_ptr<Session> session, const string &user) const
{
	bool answer = false;
	const auto token = session->get_request()->get_header(config::token_header);
	
	switch (request) {
	case AuthManager::request_t::POST:
		answer = db->is_token_exist(user, token);
		break;
	default:
		break;
	}
	return answer;
}

const string AuthManager::login(const string &user, const string &password)
{
	cout << "login..." << endl;
	auto token = utility::random_string(config::token_lenght);
	db->save_token(user, token);
	return token;
}

const void AuthManager::logout(const string& user, const string& token)
{

}