#include "MongoDriver.h"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

std::__cxx11::string MongoDriver::get_schedules()
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

std::__cxx11::string MongoDriver::get_schedule_by_id(std::string id)
{
	mongocxx::options::find opts;
	bsoncxx::builder::stream::document exclude_fields;
	exclude_fields << "odd" << 0 << "even" << 0 << "unusual" << 0 << "subjects" << 0;
	opts.projection(exclude_fields.view());
	auto cursor = db[mongo_config::c_schedules].find(document{} << "_id" << bsoncxx::oid(id) << finalize, opts);
	return bsoncxx::to_json(*cursor.begin());
}


void MongoDriver::checks()
{
	std::cout << "Mongo check" << std::endl;
	//std::cout << bsoncxx::to_json(*db[mongo_config::c_users].find({}).begin());
	//template_table();
}

void MongoDriver::template_table()
{
	auto c_schedules = db[mongo_config::c_schedules];
	//c_schedules.drop();
	
	auto c_users = db[mongo_config::c_users];
	//c_users.drop();
	
	std::string data, tmp;
	std::fstream file;
	file.open("kek.json");
	while (!file.eof()) {
		getline(file, tmp);
		data += tmp;
		data += '\n';
	}
	file.close();
	auto bson = bsoncxx::from_json(data);
	std::cout << bsoncxx::to_json(bson.view()) << std::endl;
	//c_schedules.insert_one();
	
	file.open("keku.json");
	data.clear();
	while (!file.eof()) {
		getline(file, tmp);
		data += tmp;
		data += '\n';
	}
	file.close();
	bson = bsoncxx::from_json(data);
	
	//c_users.insert_one(bson.view());	
	
	std::cout << "inserted one" << std::endl;
}
