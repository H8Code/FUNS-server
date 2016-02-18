#include "MongoDriver.h"

void MongoDriver::checks()
{
    std::cout << "Mongo check" << std::endl;
    std::cout << bsoncxx::to_json(*db[MongoDBCollections::c_test].find({}).begin());
}
