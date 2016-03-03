#ifndef FUNSRESOURCE_H
#define FUNSRESOURCE_H

#include <restbed>
#include <memory>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include "../DBDriver.h"
#include "FunsResourceImpl.h"

using namespace restbed;
using namespace std;

class FunsResource
: public Resource {
public:
	FunsResource() = delete;
	explicit FunsResource(
		const string &path,
		unique_ptr<FunsResourceImpl> impl_,
		shared_ptr<DBDriver> db,
		shared_ptr<AuthManager> auth)
	: Resource(),
	impl{std::move(impl_)}
	{
		set_path(path);
		set_method_handler("GET", std::bind(&FunsResourceImpl::get_handler, impl.get(), std::placeholders::_1));
		set_method_handler("POST", std::bind(&FunsResourceImpl::post_handler, impl.get(), std::placeholders::_1));
		set_method_handler("DELETE", std::bind(&FunsResourceImpl::delete_handler, impl.get(), std::placeholders::_1));
		
		impl->init(db, auth);
	}

private:
	unique_ptr<FunsResourceImpl> impl;
};

#endif /* FUNSRESOURCE_H */

