#ifndef SCHEDULES
#define SCHEDULES

#include <restbed>
#include <memory>
#include "../DBDriver.h"
#include <iostream>

using namespace restbed;
using namespace std;

class APISchedules
: public Resource {
public:
    APISchedules() = delete;
    explicit APISchedules(shared_ptr<DBDriver> db)
    : Resource(),
    db{db}
    {
        set_path("/api/schedules");
        set_method_handler("GET", std::bind(&APISchedules::get_handler, this, std::placeholders::_1));
    }
private:
    shared_ptr<DBDriver> db;

    void get_handler(const shared_ptr<Session> session) {
        auto data = db->get_schedules();
        session->close(OK, data);
    }
};

#endif // SCHEDULES

