#ifndef MONGODRIVER_H
#define MONGODRIVER_H

#include <iostream>
#include <fstream>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "DBDriver.h"
#include "MongoConfig.h"

#include <thread>
#include <sstream>

using namespace mongo_config;

class MongoDriver
        : public DBDriver
{
public:
    MongoDriver() {checks();};
    std::string get_driver_name() override { return "Mongoc"; }
    std::string get_schedules() override;
    std::string get_schedule_by_id(std::string id) override;

private:
    void checks();

    mongocxx::instance inst{};
    mongocxx::client mongo_client{mongocxx::uri{}};
    mongocxx::database db{mongo_client[db_name]};
};

#endif // MONGODRIVER_H
