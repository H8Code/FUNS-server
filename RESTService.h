#ifndef SERVICE_H
#define SERVICE_H

#include <memory>
#include <restbed>
#include "FunsConfig.h"
#include "DBDriver.h"
#include "api/Schedules.h"

using namespace restbed;
using namespace std;

class RESTService
{
public:
    RESTService() = delete;
    RESTService(shared_ptr<DBDriver> db);

    void start();

private:
    shared_ptr<DBDriver> db;
    shared_ptr<Settings> settings;
    shared_ptr<Service> service;
};

#endif // SERVICE_H
