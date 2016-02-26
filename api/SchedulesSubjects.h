#ifndef SCHEDULESSUBJECTS
#define SCHEDULESSUBJECTS

#include <restbed>
#include <memory>
#include "../DBDriver.h"
#include "FunsResource.h"

class APISchedulesSubjects
: public FunsResource {
public:

        APISchedulesSubjects(shared_ptr<DBDriver> db, const string &path)
        : FunsResource(db, path)
        {
        }
private:

        void get_handler(const shared_ptr<Session> session)
        {
                const auto id = session->get_request()->get_path_parameter("id", true);
                auto data = db->get_schedule_subjects_by_id(id);
                session->close(OK, data);
        }
};

#endif // SCHEDULESSUBJECTS

