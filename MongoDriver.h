#ifndef MONGODRIVER_H
#define MONGODRIVER_H

#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "DBDriver.h"
#include "MongoConfig.h"

class MongoDriver
: public DBDriver {
public:

	MongoDriver()
	{
		checks();
	};

	std::string get_driver_name() const override
	{
		return "Mongoc";
	}
	std::string get_schedules() const override;
	std::string get_schedule_by_id(const std::string &id) const override;
	std::string get_users() const override;
	std::string get_users_by_id(const std::string &id) const override;

	bool is_token_exist(const std::string &name, const std::string &token) const override;
	bool save_token(const std::string &name, const std::string &token) override;
	bool remove_token(const std::string& name, const std::string& token) override;
	bool remove_tokens(const std::string& name) override;

private:
	void checks();

	mongocxx::instance inst{};
	mongocxx::client mongo_client{mongocxx::uri
		{}};
	mongocxx::database db{mongo_client[mongo_config::db_name]};
};

#endif // MONGODRIVER_H
