#include "Utility.h"

#include <random>
#include <chrono>

using namespace std;

const string funs_utility::hash(const string &data)
{

}

const string funs_utility::random_string(const string::size_type lenght)
{
	static const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static uniform_int_distribution<uint_fast8_t> selector(0, 35);

	auto seed = static_cast<uintmax_t> (chrono::high_resolution_clock::now().time_since_epoch().count());
	static mt19937 generator(seed);

	string key = "";

	for (auto index = lenght; index > 0; --index) {
		key += charset.at(selector(generator));
	}
	return key;
}