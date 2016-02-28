#ifndef FUNSRESOURCE_H
#define FUNSRESOURCE_H

#include <restbed>
#include <memory>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include "../DBDriver.h"

using namespace restbed;
using namespace std;

class FunsResource
: public Resource {
public:
	FunsResource() = delete;
	virtual ~FunsResource() = default;
	explicit FunsResource(shared_ptr<DBDriver> _db, const string &path, shared_ptr<AuthManager> _auth = shared_ptr<AuthManager>())
	: Resource(),
	db{_db},
	auth{_auth}
	{
		set_path(path);
		set_method_handler("GET", std::bind(&FunsResource::get_handler, this, std::placeholders::_1));
		set_method_handler("POST", std::bind(&FunsResource::post_handler, this, std::placeholders::_1));
	}
protected:
	shared_ptr<DBDriver> db;
	shared_ptr<AuthManager> auth;

	static const string __get_field_from_bytes(const Bytes &body, const string & field)
	{
		const auto doc = bsoncxx::from_json(string{body.begin(), body.end()});
		const auto creator_b = doc.view()[field].get_utf8().value;
		return {creator_b.begin(), creator_b.end()};
	};

private:

	virtual void get_handler(const shared_ptr<Session> session)
	{
		session->close(NOT_IMPLEMENTED);
	};

	virtual void post_handler(const shared_ptr<Session> session)
	{
		session->close(NOT_IMPLEMENTED);
	};
};

#endif /* FUNSRESOURCE_H */

