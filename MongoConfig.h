#ifndef MONGODBCOLLECTIONS
#define MONGODBCOLLECTIONS

#include "FunsConfig.h"

namespace mongo_config {
	auto get_param_ = [] (auto param, auto default_value)
	{
			if (funs::config::config_reader->defaults_only__)
				goto mongo_return_default_val_;
			try {
				auto value = default_value;
				if (not funs::config::config_reader->get_block("mongo").lookupValue(param, value))
					std::cout << "No " << param
					<< " found, using default " << value << std::endl;
				return value;
			} catch (...) {
				goto mongo_return_default_val_;
			}
mongo_return_default_val_:
			return default_value;
	};

	const auto mongo_uri{get_param_("uri", "mongodb://127.0.0.1")};
	constexpr auto db_name{"funs"};
	constexpr auto c_test{"test_collection"};
	constexpr auto c_schedules{"schedules"};
	constexpr auto c_users{"users"};
}

#endif // MONGODBCOLLECTIONS

