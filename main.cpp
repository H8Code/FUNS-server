#include <iostream>
#include <memory>
#include "RESTService.h"
#include "MongoDriver.h"
#include "Utility.h"


std::shared_ptr<DBDriver> db
{
	std::make_shared<MongoDriver>()
};

void hello()
{
	funs::utility::log()->info() << "FUNS-server. Version " << 1 << "." << 0 << "\n";
	funs::utility::log()->info() << "Using " << db->get_driver_name() << " driver.";
}

int main(const int, const char**)
{
	try {
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
		sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_st>(funs::config::log_file));
		auto combined_logger = std::make_shared<spdlog::logger>("log", begin(sinks), end(sinks));
		spdlog::register_logger(combined_logger);
	} catch (const spdlog::spdlog_ex& ex) {
		std::cout << "Log failed: " << ex.what() << std::endl;
	}
	try {
		hello();
		auto s = std::make_shared<RESTService>(db);
		s->start();
	} catch (const std::exception& ex) {
		std::cerr << "UNEXPECTED ERROR: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
