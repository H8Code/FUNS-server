#ifndef UTILITY_H
#define UTILITY_H

#include <string>

namespace funs{
namespace utility {
	auto
	hash(const std::string &data)
	-> const std::string;

	auto
	random_string(const std::string::size_type lenght)
	-> const std::string;
}
}

#endif /* UTILITY_H */

