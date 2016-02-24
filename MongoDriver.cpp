#include "MongoDriver.h"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

std::string MongoDriver::get_schedules()
{
	mongocxx::options::find opts;
	bsoncxx::builder::stream::document exclude_fields;
	exclude_fields << "odd" << 0 << "even" << 0 << "unusual" << 0 << "subjects" << 0;
	opts.projection(exclude_fields.view());
	auto cursor = db[mongo_config::c_schedules].find({}, opts);
	std::string result{};
	result += "[";
	for (auto &&doc : cursor)
		result += bsoncxx::to_json(doc) += ", ";
	result += "]";
	return result;
}

std::string MongoDriver::get_schedule_by_id(std::string id)
{
	mongocxx::options::find opts;
	bsoncxx::builder::stream::document exclude_fields;
	exclude_fields << "odd" << 0 << "even" << 0 << "unusual" << 0 << "subjects" << 0;
	opts.projection(exclude_fields.view());
	auto cursor = db[mongo_config::c_schedules].find(document{} << "_id" << bsoncxx::oid(id) << finalize, opts);
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