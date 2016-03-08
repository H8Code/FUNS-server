#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h++>
#include <memory>

#include "Utility.h"

namespace funs {
	namespace config {
		constexpr auto config_file_name = "funs.conf";

		class ___ConfigReader___ {
		public:
			bool defaults_only__;
			___ConfigReader___() :
			defaults_only__{false},
			c__{std::make_unique<libconfig::Config>()}
			{
				try {
					init(config_file_name);
				} catch (...) {
					std::cerr << "No correct funs.conf found, using default values." << std::endl;
					defaults_only__ = true;
					c__.reset();
					return;
				}
				try {
					std::string name = c__->lookup("name");
					std::cout << name << " config" << std::endl;
				} catch (const libconfig::SettingNotFoundException &nfex) {
					std::cerr
						<< "No 'name' setting in configuration file."
						<< std::endl;
				}
			}

			const libconfig::Setting & get_block(auto block_name) const
			{
				try {
					const libconfig::Setting &block =
						c__->getRoot()[block_name];
					return block;
				} catch (const libconfig::SettingNotFoundException &nfex) {
					std::cout << "No " << block_name << " config block found." << std::endl;
					throw nfex;
				}
			}

		private:
			std::unique_ptr<libconfig::Config> c__;

			void init(auto filename)
			{
				try {
					c__->readFile(filename);
				} catch (const libconfig::FileIOException &fioex) {
					std::cerr << "I/O error while reading config file " << filename << std::endl;
					throw fioex;
				} catch (const libconfig::ParseException &pex) {
					std::cerr << "Parse error at "
						<< pex.getFile() << ":" << pex.getLine()
						<< " - " << pex.getError() << std::endl;
					throw pex;
				}
			}
		};
		static std::unique_ptr<___ConfigReader___> config_reader = std::make_unique<___ConfigReader___>();

		auto get_param_ = [] (auto param, auto default_value)
		{
			if (config_reader->defaults_only__)
				goto funs_return_default_val_;
			try {
				auto value = default_value;
				if (not config_reader->get_block("funs").lookupValue(param, value))
					std::cout << "No " << param
					<< " found, using default " << value << std::endl;
				return value;
			} catch (...) {
				goto funs_return_default_val_;
			}
funs_return_default_val_:
			return default_value;
		};

		const auto port = get_param_("port", 34666);
		const auto bind_addres = get_param_("bind_address", "127.0.0.1");
		const auto worker_limit = get_param_("service_threads", 4);
		constexpr auto token_header = "Authorization";
		constexpr auto token_lenght = 32;
		constexpr auto salt_lenght = 32;
		const auto log_file = get_param_("log_file", "log");
	}
}

#endif // CONFIG_H

