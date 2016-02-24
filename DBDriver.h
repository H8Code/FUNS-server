#ifndef DBDRIVER_H
#define DBDRIVER_H
#include <string>

/*
 * Database driver interface
 */
class DBDriver {
public:
    virtual std::string get_driver_name() const = 0;
    virtual std::string get_schedules() const = 0;
    virtual std::string get_schedule_by_id(std::string id) const = 0;
    virtual std::string get_users() const = 0;
    virtual std::string get_users_by_id(std::string id) const = 0;
};

#endif //DBDRIVER_H
