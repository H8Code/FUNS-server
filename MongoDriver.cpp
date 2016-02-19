#include "MongoDriver.h"

#include <thread>
#include <sstream>

std::__cxx11::string MongoDriver::get_schedules()
{
    bsoncxx::builder::stream::document doc;
    std::stringstream ss;
    ss << std::this_thread::get_id( );
    // maybe we need mutexes, cuz mongo driver is not async
    doc << "name" << "check" << "thread" << ss.str();
    return bsoncxx::to_json(doc);
}

void MongoDriver::checks()
{
    std::cout << "Mongo check" << std::endl;
    std::cout << bsoncxx::to_json(*db[mongo_config::c_test].find({}).begin());
}
