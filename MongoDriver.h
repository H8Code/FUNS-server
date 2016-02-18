#ifndef MONGODRIVER_H
#define MONGODRIVER_H

#include <iostream>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "DBDriver.h"
#include "MongoDBCollections.h"

using namespace MongoDBCollections;

class MongoDriver : public DBDriver
{
public:
    MongoDriver() {checks(); }
    std::string getDriverName() override { return "Mongoc"; }

private:
    void checks();

    mongocxx::instance inst{};
    mongocxx::client mongo_client{mongocxx::uri{}};
    mongocxx::database db{mongo_client[db_name]};
};

#endif // MONGODRIVER_H
