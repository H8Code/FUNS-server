#include "MongoDriver.h"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

/*
 * Will create opts variable, used for excluding fields from find requests
 */
#define __excluder(list...) \
	mongocxx::options::find opts; \
	bsoncxx::builder::stream::document exclude_fields; \
	for (auto &x: list) exclude_fields << x << 0; \
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
 * List type for macro-lists
 */
using __list_t = std::initializer_list<std::string>;

std::string MongoDriver::get_schedules() const
{
	__list_t exclude = {"odd", "even", "unusual", "subjects"};
	__find_all_and_exclude(mongo_config::c_schedules, exclude)
}

std::string MongoDriver::get_schedule_by_id(std::string id) const
{
	__list_t exclude = {"odd", "even", "unusual", "subjects"};
	__find_id_and_exclude(mongo_config::c_schedules, bsoncxx::oid(id), exclude)
}

std::string MongoDriver::get_users() const
{
	__list_t exclude = {"password_hash", "salt"};
	__find_all_and_exclude(mongo_config::c_users, exclude)}

std::string MongoDriver::get_users_by_id(std::string id) const
{
	__list_t exclude = {"password_hash", "salt"};
	__find_id_and_exclude(mongo_config::c_users, id, exclude)
}

void MongoDriver::checks()
{
	std::cout << "Mongo check" << std::endl;
	//std::cout << bsoncxx::to_json(*db[mongo_config::c_users].find({}).begin());
	//template_table();
}