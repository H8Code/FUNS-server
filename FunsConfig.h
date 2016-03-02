#ifndef CONFIG_H
#define CONFIG_H

namespace funs {
namespace config {
	constexpr auto port = 34666;
	constexpr auto bind_addres = "127.0.0.1";
	constexpr auto worker_limit = 4;
	constexpr auto token_header = "Authorization";
	constexpr auto token_lenght = 32;
	constexpr auto salt_lenght = 32;
}
}

#endif // CONFIG_H

