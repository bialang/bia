#include <CLI/CLI.hpp>
#include <bia/bia.hpp>
#include <fstream>

int main(int argc, char** argv)
{
	CLI::App app{
		"Bia command line tool used for executing, compiling, packaging and installing scripts/modules"
	};

	app.set_help_all_flag("--help-all", "Expand help all");
	app.set_help_flag("-h,--help", "Expand quick help");

	auto run = app.add_subcommand("run", "run a given source file");

	std::string file;
	std::vector<std::string> args;

	run->add_option("source", file, "the source file")->required()->check(CLI::ExistingFile);
	run->add_option("args", args, "the remaining arguments that are passed to the script");

	app.require_subcommand(0, 1);

	CLI11_PARSE(app, argc, argv);

	if (app.get_subcommands()[0] == run) {
		bia::engine engine;
		std::vector<const char*> arg_ptrs;

		arg_ptrs.reserve(args.size());

		for (const auto& i : args) {
			arg_ptrs.push_back(i.c_str());
		}

		engine.use_bsl({ arg_ptrs.data(), arg_ptrs.data() + arg_ptrs.size() });

		std::ifstream f{ file, std::ios::in | std::ios::binary };

		if (!f.is_open()) {
			std::cerr << "failed to open '" << file << "'\n";

			return 1;
		}

		engine.execute(f);
	}

	return 0;
}
