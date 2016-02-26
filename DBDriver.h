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
    virtual std::string get_schedule_odd_by_id(const std::string &id) const = 0;
    virtual std::string get_schedule_by_id(const std::string &id) const = 0;
    virtual std::string get_users() const = 0;
    virtual std::string get_users_by_id(const std::string &id) const = 0;
    
    virtual bool is_token_exist(const std::string &name, const std::string &token) const = 0;
    virtual bool save_token(const std::string &name, const std::string &token) = 0;
    virtual bool remove_token(const std::string &name, const std::string &token) = 0;
    virtual bool remove_tokens(const std::string &name) = 0;
};

#endif //DBDRIVER_H
