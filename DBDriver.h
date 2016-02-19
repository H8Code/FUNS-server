#ifndef DBDRIVER_H
#define DBDRIVER_H
#include <string>

/*
 * Database driver interface
 */
class DBDriver {
public:
    virtual std::string get_driver_name() = 0;
    virtual std::string get_schedules() = 0;
};

#endif //DBDRIVER_H
