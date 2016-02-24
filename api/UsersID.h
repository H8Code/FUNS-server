#ifndef USERSID_H
#define USERSID_H

#include "FunsResource.h"

class APIUsersID
: public FunsResource {
public:
    APIUsersID(shared_ptr<DBDriver> db, const string &path)
    : FunsResource(db, path) {}
private:
    void get_handler(const shared_ptr<Session> session) override
    {
        session->close(OK, "users_id get");
    }
};

#endif /* USERSID_H */

