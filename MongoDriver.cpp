#include "MongoDriver.h"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::finalize;

using find_opts_t = mongocxx::options::find;

/*
 * Will create opts variable, used for excluding(and including) fields from find requests
 */
#define __excluder(list...) \
	mongocxx::options::find opts; \
	bsoncxx::builder::stream::document exclude_fields; \
	for (auto &x: list) exclude_fields << x << 0; \
	opts.projection(exclude_fields.view());

#define __includer(list...) \
	mongocxx::options::find opts; \
	bsoncxx::builder::stream::document exclude_fields; \
	for (auto &x: list) exclude_fields << x << 1; \
	opts.projection(exclude_fields.view());

/*
 * Will return all documents from collection, excluding fields "exclude"
 */
#define __find_all_and_exclude(collection, exclude) \
	__excluder(exclude); \
	auto cursor = db[collection].find({}, opts); \
	std::string result{}; \
	result += "["; \
	for (auto &&doc : cursor) result += bsoncxx::to_json(doc) += ", "; \
	result += "]"; \
	return result;

/*
 * Will return documents from collection with matching id, excluding fields "exclude"
 */
#define __find_id_and_exclude(collection, id, exclude) \
	__excluder(exclude); \
	auto cursor = db[collection] \
	.find( document{} << "_id" << id << finalize, opts); \
	return bsoncxx::to_json(*cursor.begin());

/*
 * Will return documents from collection with matching id, including fields "include"
 */

#define __find_id_and_include(collection, id, include) \
	__includer(include); \
	auto cursor = db[collection] \
	.find( document{} << "_id" << id << finalize, opts); \
	return bsoncxx::to_json(*cursor.begin());

#define __opts_Xclude_fields(__opts, __list, __X) \
	bsoncxx::builder::stream::document __Xclude_fields; \
	for (auto &x: __list) __Xclude_fields << x << __X; \
	__opts.projection(__Xclude_fields.view());

#define __find_one_with_opts(__collection, __id,  __opts) \
	auto result = db[__collection] \
	.find_one( document{} << "_id" << __id<< finalize, __opts); \

#define __find_all_with_opts(__collection, __opts) \
	auto result = db[__collection] \
	.find( {},__opts);

/*
 * List type for macro-lists
 */
using list_t__ = std::initializer_list<std::string>;

std::string MongoDriver::get_schedules() const
{
//	__list_t exclude = {"odd", "even", "unusual", "subjects"};
//	__find_all_and_exclude(mongo_config::c_schedules, exclude)
	list_t__ list = {"odd", "even", "unusual", "subjects"};
	find_opts_t opts;
	__opts_Xclude_fields(opts, list, 0);
	__find_all_with_opts(mongo_config::c_schedules, opts);

	std::string c_result;
	c_result += "[";
	for (auto &&doc : result) c_result += bsoncxx::to_json(doc) += ", ";
	c_result += "]";
	return c_result;
}

std::string MongoDriver::get_schedule_odd_by_id(const std::string &id) const
{
	list_t__ list = {"odd"};
	find_opts_t opts;
	__opts_Xclude_fields(opts, list, 1);
	__find_one_with_opts(mongo_config::c_schedules, bsoncxx::oid(id), opts);
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view()["odd"].get_array().value);
}

std::string MongoDriver::get_schedule_even_by_id(const std::string &id) const
{
	list_t__ list = {"even"};
	find_opts_t opts;
	__opts_Xclude_fields(opts, list, 1);
	__find_one_with_opts(mongo_config::c_schedules, bsoncxx::oid(id), opts);
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view()["even"].get_array().value);
}

std::string MongoDriver::get_schedule_unusual_by_id(const std::string &id) const
{
	list_t__ list = {"unusual"};
	find_opts_t opts;
	__opts_Xclude_fields(opts, list, 1);
	__find_one_with_opts(mongo_config::c_schedules, bsoncxx::oid(id), opts);
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view()["unusual"].get_array().value);
}

std::string MongoDriver::get_schedule_subjects_by_id(const std::string &id) const
{
	list_t__ list = {"subjects"};
	find_opts_t opts;
	__opts_Xclude_fields(opts, list, 1);
	__find_one_with_opts(mongo_config::c_schedules, bsoncxx::oid(id), opts)
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view()["subjects"].get_array().value);
}

std::string MongoDriver::get_schedule_by_id(const std::string &id) const
{
	list_t__ list = {"odd", "even", "unusual", "subjects"};
	find_opts_t opts;
	__opts_Xclude_fields(opts, list, 0);
	__find_one_with_opts(mongo_config::c_schedules, bsoncxx::oid(id), opts)
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view());
}

std::string MongoDriver::get_users() const
{
	list_t__ exclude = {"password_hash", "salt"};
	__find_all_and_exclude(mongo_config::c_users, exclude)
}

std::string MongoDriver::get_users_by_id(const std::string &id) const
{
	list_t__ list = {"password_hash", "salt"};
	find_opts_t opts;
	__opts_Xclude_fields(opts, list, 0);
	__find_one_with_opts(mongo_config::c_users, id, opts)
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view());
}

bool MongoDriver::is_token_exist(const std::string &name, const std::string &token) const
{
	auto result = db[mongo_config::c_users].find_one(document{}
	<< "_id" << name << "tokens.token" << token
		<< finalize);
	if (result == bsoncxx::stdx::nullopt)
		return false;
	else
		return true;
}

bool MongoDriver::save_token(const std::string &name, const std::string &token)
{
	bsoncxx::builder::stream::document upd, filter;
	filter << "_id" << name << finalize;
	upd << "$push" << open_document << "tokens" << open_document << "token" << token << close_document << close_document;

	auto ans = db[mongo_config::c_users].update_one(filter.view(), upd.view());
	if (ans.value().modified_count() == 1)
		return true;
	else
		return false;
}

bool MongoDriver::remove_token(const std::string& name, const std::string& token)
{
	bsoncxx::builder::stream::document upd, filter;
	filter << "_id" << name << finalize;
	upd << "$pull" << open_document << "tokens" << open_document << "token" << token << close_document << close_document;

	auto ans = db[mongo_config::c_users].update_one(filter.view(), upd.view());
	if (ans.value().modified_count() == 1)
		return true;
	else
		return false;
}

bool MongoDriver::remove_tokens(const std::string& name)
{
	return false;
}

bool MongoDriver::get_password_hash_and_salt(const std::string& name, std::string& password, std::string& salt) const
{
	return false;
}

bool MongoDriver::save_password_hash_and_salt(const std::string& name, const std::string& password, const std::string& salt)
{
	return false;
}

bool MongoDriver::register_user(const std::string& name, const std::string& password, const std::string& salt, const std::string& forename, const std::string& info)
{
	return false;
}
