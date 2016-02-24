#ifndef USERS_H
#define USERS_H

#include "FunsResource.h"

class APIUsers
: public FunsResource {
public:
    APIUsers(shared_ptr<DBDriver> db, const string &path)
    : FunsResource(db, path) {}
private:
    void get_handler(const shared_ptr<Session> session) override
    {
        session->close(OK, "users get");
    }
};


#endif /* USERS_H */

