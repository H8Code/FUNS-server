#ifndef SCHEDULESID
#define SCHEDULESID

#include <restbed>
#include <memory>
#include "../DBDriver.h"
#include <iostream>

using namespace restbed;
using namespace std;

class APISchedulesID
: public Resource {
public:
    APISchedulesID() = delete;
    explicit APISchedulesID(shared_ptr<DBDriver> db)
    : Resource(),
    db{db}
    {
        set_path("/api/schedules/{id: .*}");
        set_method_handler("GET", std::bind(&APISchedulesID::get_handler, this, std::placeholders::_1));
    }
private:
    shared_ptr<DBDriver> db;

    void get_handler(const shared_ptr<Session> session) {
        const auto id = session->get_request()->get_path_parameter("id",true);
        auto data = db->get_schedule_by_id(id);
        session->close(OK, data);
    }
};

#endif // SCHEDULESID

