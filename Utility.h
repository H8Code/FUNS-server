#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>

#ifdef FUNS_DEBUG

#define L(x) \
	std::cout << "DEBUG: " << x << std::endl;

#endif

namespace funs{
namespace utility {
	constexpr auto __max_using_before_reseed = 100;
	auto
	hash(const std::string &data)
	-> const std::string;

	auto
	random_string(const std::string::size_type lenght)
	-> const std::string;
	
	auto seed()
	-> uintmax_t;
	
	auto make_JSON_array_from_cursor(const auto &cursor)
	-> std::string;
}
}

#endif /* UTILITY_H */

