#ifndef SERVICE_H
#define SERVICE_H

#include <memory>
#include <restbed>
#include "Config.h"
#include "DBDriver.h"
#include "resources/Schedules.h"

using namespace restbed;
using namespace std;

class FUNSService
{
public:
    FUNSService() = delete;
    FUNSService(shared_ptr<DBDriver> db);

    void start();

private:
    shared_ptr<DBDriver> db;
    shared_ptr<Settings> settings;
    shared_ptr<Service> service;
};

#endif // SERVICE_H
