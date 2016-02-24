#ifndef SCHEDULES
#define SCHEDULES

#include <restbed>
#include <memory>
#include "../DBDriver.h"
#include "FunsResource.h"

using namespace restbed;
using namespace std;

class APISchedules
: public FunsResource {
public:
    APISchedules(shared_ptr<DBDriver> db, const string &path)
    : FunsResource(db, path) {}
private:
    void get_handler(const shared_ptr<Session> session) override
    {
        auto data = db->get_schedules();
        session->close(OK, data);
    }
};

#endif // SCHEDULES

