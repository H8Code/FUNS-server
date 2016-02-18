#ifndef DBDRIVER_H
#define DBDRIVER_H
#include <string>

/*
 * Database driver interface
 */
class DBDriver
{
public:
    virtual std::string getDriverName() = 0;
    virtual std::string getSchedules() = 0;
};

#endif //DBDRIVER_H
