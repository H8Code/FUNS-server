#ifndef CONFIG_H
#define CONFIG_H

namespace funs_config {
	constexpr auto port = 34666;
	constexpr auto bind_addres = "127.0.0.1";
	constexpr auto worker_limit = 4;
	constexpr auto token_header = "Token";
	constexpr auto token_lenght = 32;
}

#endif // CONFIG_H

