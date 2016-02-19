#include "MongoDriver.h"

#include <thread>
#include <sstream>

std::__cxx11::string MongoDriver::get_schedules()
{
	auto cursor = db[mongo_config::c_schedules].find({});
	std::string result{};
	result += "[";
	for (auto &&doc : cursor)
		result += bsoncxx::to_json(doc) += ", ";
	result += "]";
	return result;
}

void MongoDriver::checks()
{
	std::cout << "Mongo check" << std::endl;
	std::cout << bsoncxx::to_json(*db[mongo_config::c_test].find({}).begin());
}
