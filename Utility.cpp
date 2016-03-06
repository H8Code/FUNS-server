#include "Utility.h"

#include <random>
#include <limits>
#include <exception>
#include <mhash.h>
#include <mongocxx/v_noabi/mongocxx/cursor.hpp>

constexpr auto __HASH_ID = MHASH_MD5;

using namespace std;

const string funs::utility::hash(const string &data)
{
	auto hasher = mhash_init(__HASH_ID);
	const auto block_size = mhash_get_block_size(__HASH_ID);
	if (hasher == MHASH_FAILED)
		throw runtime_error(":c");

	uint8_t hash[block_size],
		buffer[data.size()];

	memcpy(buffer, data.c_str(), data.size());
	mhash(hasher, &buffer, block_size);
	mhash_deinit(hasher, &hash);
	string ret(block_size, '-');
	for (remove_cv < decltype(block_size)>::type i = 0; i < block_size; ++i)
		ret[i] = hash[i];
	return ret;
}

const string funs::utility::random_string(const string::size_type lenght)
{
	constexpr uint8_t first_ASCII_symbol{0x20};
	constexpr uint8_t last_ASCII_symbol{0x7E};
	static uniform_int_distribution<uint_fast8_t> selector(first_ASCII_symbol, last_ASCII_symbol);

	static mt19937_64 generator{};
	static remove_cv < decltype(funs::utility::__max_using_before_reseed)>::type used_times{0};

	if (used_times++ > funs::utility::__max_using_before_reseed)
		generator.seed(funs::utility::seed());

	string key(lenght, '-');

	for (auto &x : key)
		x = selector(generator);
	return key;
}

uintmax_t funs::utility::seed()
{
	static random_device rnd;
	static uniform_int_distribution<uintmax_t> dist{
		numeric_limits<uintmax_t>::lowest(),
		numeric_limits<uintmax_t>::max()
	};
	return dist(rnd);
}

string funs::utility::make_JSON_array_from_cursor(mongocxx::cursor &cursor)
{
	constexpr auto
		open__ = '[',
		close__ = ']',
		delim__ = ',';

	string result{};
	result += open__;

	for (auto &&doc : cursor)
		result += bsoncxx::to_json(doc) += delim__;

	if (result.size() not_eq 1)
		*result.rbegin() = close__;
	else
		result += close__;
	return result;
}

string funs::utility::field_from_JSON_bytes(const restbed::Bytes &body, const std::string &field)
{
	const auto doc = bsoncxx::from_json(string{body.begin(), body.end()});
	const auto creator_b = doc.view()[field].get_utf8().value;
	return string{creator_b.begin(), creator_b.end()};
}