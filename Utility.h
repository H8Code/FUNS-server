#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <restbed>
#include <memory>

#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/cursor.hpp>

#include <spdlog/spdlog.h>

namespace funs {
	namespace utility {

		inline
		std::shared_ptr<spdlog::logger>
		log()
		{
			return spdlog::get("log");
		}

		constexpr auto __max_using_before_reseed = 100;

		auto
		hash(const std::string &data)
		-> const std::string;

		auto
		random_string(const std::string::size_type lenght)
		-> const std::string;

		auto seed()
		-> uintmax_t;

		auto make_JSON_array_from_cursor(const std::string &key, mongocxx::cursor &cursor)
		-> std::string;

		auto field_from_JSON_bytes(const restbed::Bytes &body, const std::string &field)
		-> std::string;
		
		auto inline token_to_JSON(const auto &token)
		-> std::string
		{
			return R"({"token":")" + token + R"("})";
		}
		
		auto inline quotes_remover(const auto& s)
		-> std::string
		{
			return std::string(++s.begin(), --s.end());
		};
	}
}

#endif /* UTILITY_H */

