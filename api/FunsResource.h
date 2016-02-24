#ifndef FUNSRESOURCE_H
#define FUNSRESOURCE_H

#include <restbed>
#include <memory>
#include "../DBDriver.h"

using namespace restbed;
using namespace std;

class FunsResource
: public Resource {
public:
    FunsResource() = delete;
    explicit FunsResource(shared_ptr<DBDriver> _db, const string &path)
    : Resource(),
    db{_db}
    {
        set_path(path);
        set_method_handler("GET", std::bind(&FunsResource::get_handler, this, std::placeholders::_1));
    }
private:
    shared_ptr<DBDriver> db;

    virtual void get_handler(const shared_ptr<Session> session) = 0;
};

#endif /* FUNSRESOURCE_H */

