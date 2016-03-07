#include "MongoDriver.h"
#include "Utility.h"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::finalize;
using namespace std;

using list_t__ = std::initializer_list<string>;

template<class opts_t, class stream_t, class list_t, class param_t>
opts_t MongoDriver::Xcluder(const list_t& list, const param_t param)
{
	stream_t stream;
	for (auto &&x : list) stream << x << param;
	opts_t opts;
	opts.projection(stream.extract());
	return opts;
}

mongocxx::cursor MongoDriver::find_all(mongocxx::collection collection, bsoncxx::document::view_or_value request, mongocxx::options::find &opts)
{
	return collection.find(move(request), opts);
}

optional_t<bsoncxx::document::value> MongoDriver::find_one(mongocxx::collection collection, bsoncxx::document::view_or_value request, mongocxx::options::find &opts)
{
	return collection.find_one(move(request), opts);
}

std::string MongoDriver::find_one_and_get_field(mongocxx::collection &&collection, const string &id, const string &field)
{
	auto opts = Xcluder(list_t__{field}, 1);
	
	auto result = find_one(move(collection),
		document
	{}
	<< "_id" << bsoncxx::oid(id) << finalize,
		opts);
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view()[field].get_value());
}

std::string MongoDriver::get_schedules() const
{
	list_t__ list = {"odd", "even", "unusual", "subjects"};
	auto opts = Xcluder(list, 0);
	lock_guard<mutex> db_lock(db_mutex);
	auto result = find_all(db[mongo_config::c_schedules],{}, opts);
	return funs::utility::make_JSON_array_from_cursor(result);
}

std::string MongoDriver::get_schedule_odd_by_id(const std::string &id) const
{
	lock_guard<mutex> db_lock(db_mutex);
	return find_one_and_get_field(db[mongo_config::c_schedules], id, "odd");
}

std::string MongoDriver::get_schedule_even_by_id(const std::string &id) const
{
	lock_guard<mutex> db_lock(db_mutex);
	return find_one_and_get_field(db[mongo_config::c_schedules], id, "even");
}

std::string MongoDriver::get_schedule_unusual_by_id(const std::string &id) const
{
	lock_guard<mutex> db_lock(db_mutex);
	return find_one_and_get_field(db[mongo_config::c_schedules], id, "unusual");
}

std::string MongoDriver::get_schedule_subjects_by_id(const std::string &id) const
{
	lock_guard<mutex> db_lock(db_mutex);
	return find_one_and_get_field(db[mongo_config::c_schedules], id, "subjects");
}

std::string MongoDriver::get_schedule_by_id(const std::string &id) const
{
	list_t__ list = {"odd", "even", "unusual", "subjects"};
	auto opts = Xcluder(list, 0);
	lock_guard<mutex> db_lock(db_mutex);
	auto result = find_one(db[mongo_config::c_schedules],
		document{}
	<< "_id" << bsoncxx::oid(id) << finalize,
		opts);
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view());
}

std::string MongoDriver::get_users() const
{
	list_t__ list = {"password_hash", "salt"};
	auto opts = Xcluder(list, 0);
	lock_guard<mutex> db_lock(db_mutex);
	auto cursor = find_all(db[mongo_config::c_users],{}, opts);
	return funs::utility::make_JSON_array_from_cursor(cursor);
}

std::string MongoDriver::get_users_by_id(const std::string &id) const
{
	list_t__ list = {"password_hash", "salt"};
	auto opts = Xcluder(list, 0);
	lock_guard<mutex> db_lock(db_mutex);
	auto result = find_one(db[mongo_config::c_users],
		document{}
	<< "_id" << id << finalize,
		opts);
	db_mutex.unlock();
	if (result == bsoncxx::stdx::nullopt)
		return "";
	else
		return bsoncxx::to_json(result.value().view());
}

bool MongoDriver::is_token_exist(const std::string &name, const std::string &token) const
{
	lock_guard<mutex> db_lock(db_mutex);
	auto result = db[mongo_config::c_users].find_one(document{}
	<< "_id" << name << "tokens.token" << token
		<< finalize);
	db_mutex.unlock();
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

	lock_guard<mutex> db_lock(db_mutex);
	auto ans = db[mongo_config::c_users].update_one(filter.view(), upd.view());
	db_mutex.unlock();
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

	lock_guard<mutex> db_lock(db_mutex);
	auto ans = db[mongo_config::c_users].update_one(filter.view(), upd.view());
	db_mutex.unlock();
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
