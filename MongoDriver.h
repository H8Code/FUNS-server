#ifndef MONGODRIVER_H
#define MONGODRIVER_H

#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <utility>

#include "DBDriver.h"
#include "MongoConfig.h"

class MongoDriver
: public DBDriver {
public:

	MongoDriver() = default;

	std::string get_driver_name() const override
	{
		return "Mongoc";
	}
	std::string get_schedules() const override;
	std::string get_schedule_odd_by_id(const std::string &id) const override;
	std::string get_schedule_even_by_id(const std::string &id) const override;
	std::string get_schedule_unusual_by_id(const std::string &id) const override;
	std::string get_schedule_subjects_by_id(const std::string &id) const override;
	std::string get_schedule_by_id(const std::string &id) const override;
	std::string get_users() const override;
	std::string get_users_by_id(const std::string &id) const override;

	bool is_token_exist(const std::string &name, const std::string &token) const override;
	bool save_token(const std::string &name, const std::string &token) override;
	bool remove_token(const std::string& name, const std::string& token) override;
	bool remove_tokens(const std::string& name) override;
	bool get_password_hash_and_salt(const std::string& name, std::string& password, std::string& salt) const override;
	bool save_password_hash_and_salt(const std::string& name, const std::string& password, const std::string& salt) override;
	bool register_user(const std::string& name, const std::string& password, const std::string& salt, const std::string& forename, const std::string& info) override;




private:
	mongocxx::instance inst{};
	mongocxx::client mongo_client{mongocxx::uri
		{}};
	mongocxx::database db{mongo_client[mongo_config::db_name]};

	template<class opts_t = mongocxx::options::find,
	class stream_t = bsoncxx::builder::stream::document,
	class list_t, class param_t>
	static opts_t Xcluder(list_t const &list, param_t const param);
};


#endif // MONGODRIVER_H
