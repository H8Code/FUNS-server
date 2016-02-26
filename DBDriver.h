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
        virtual std::string get_schedule_even_by_id(const std::string &id) const = 0;
        virtual std::string get_schedule_unusual_by_id(const std::string &id) const = 0;
        virtual std::string get_schedule_subjects_by_id(const std::string &id) const = 0;
	virtual std::string get_schedule_by_id(const std::string &id) const = 0;
	virtual std::string get_users() const = 0;
	virtual std::string get_users_by_id(const std::string &id) const = 0;

	/*
	 * Returns true if user and token exists
	 */
	virtual bool is_token_exist(const std::string &name, const std::string &token) const = 0;
	/*
	 * Returns true if users exists and token saved
	 */
	virtual bool save_token(const std::string &name, const std::string &token) = 0;
	/*
	 * Returns true if user exist and token removed
	 */
	virtual bool remove_token(const std::string &name, const std::string &token) = 0;
	/*
	 * Returns true if user exists and tokens removed
	 */
	virtual bool remove_tokens(const std::string &name) = 0;
	/*
	 * Returns true if user exists and save password hash and salt in variables
	 */
		virtual bool get_password_hash_and_salt(const std::string &name,
		std::string &password, std::string &salt) const = 0;
	/*
	 * Returns true if user exists and new hash and salt are saved
	 */
	virtual bool save_password_hash_and_salt(const std::string &name,
		const std::string &password, const std::string &salt) = 0;
	/*
	 * Returns true if registered
	 */
	virtual bool register_user(const std::string &name,
		const std::string &password, const std::string &salt,
		const std::string &forename, const std::string &info) = 0;
};

#endif //DBDRIVER_H
