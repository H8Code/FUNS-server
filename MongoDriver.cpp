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

mongocxx::options::find excluder(std::initializer_list<std::string> list)
{
	mongocxx::options::find opts;
	bsoncxx::builder::stream::document exclude_fields;
	for (auto &x : list) exclude_fields << x << 0;
	opts.projection(exclude_fields.view());
	return opts;
}

std::string MongoDriver::get_schedules()
{
	__excluder(std::initializer_list<std::string>({"odd", "even", "unusual", "subjects"}));
	auto cursor = db[mongo_config::c_schedules]
	.find({}, opts);
	
	std::string result{};
	result += "[";
	for (auto &&doc : cursor)
		result += bsoncxx::to_json(doc) += ", ";
	result += "]";
	return result;
}

std::string MongoDriver::get_schedule_by_id(std::string id)
{
	__excluder(std::initializer_list<std::string>({"odd", "even", "unusual", "subjects"}));
	auto cursor = db[mongo_config::c_schedules]
		.find(
		document{}
	<< "_id" << bsoncxx::oid(id) << finalize,
		opts);
	return bsoncxx::to_json(*cursor.begin());
}

std::string MongoDriver::get_users()
{
	return " ";
}

std::string MongoDriver::get_users_by_id(std::string id)
{
	return " ";
}

void MongoDriver::checks()
{
	std::cout << "Mongo check" << std::endl;
	//std::cout << bsoncxx::to_json(*db[mongo_config::c_users].find({}).begin());
	//template_table();
}