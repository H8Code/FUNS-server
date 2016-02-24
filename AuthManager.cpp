#include <iostream>
#include <bits/c++config.h>

#include "AuthManager.h"
#include "FunsConfig.h"

bool AuthManager::allow(request_t request, const shared_ptr<Session> session, const string &user) const
{
	bool answer = false;
	const auto token = session->get_request()->get_header(funs_config::token_header);
	
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
	auto token = gen_token();
	db->save_token(user, token);
	return token;
}

const void AuthManager::logout(const string& user, const string& token)
{

}


const string AuthManager::gen_token()
{
	static const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static uniform_int_distribution<uint_fast8_t> selector(0, 35);

	auto seed = static_cast<uintmax_t> (chrono::high_resolution_clock::now().time_since_epoch().count());
	static mt19937 generator(seed);

	string key = "";

	for (int index = 0; index < 32; index++) {
		key += charset.at(selector(generator));
	}
	return key;
}


