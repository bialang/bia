#include "run.hpp"
#include "version.hpp"

#include <CLI/CLI.hpp>
#include <bia/bia.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
try {
	CLI::App app{
		"Bia command line tool used for executing, compiling, packaging and installing scripts/modules"
	};

	app.set_help_all_flag("--help-all", "expand help all");
	app.set_help_flag("-h,--help", "expand quick help");

	run run{ app };
	version version{ app };

	app.require_subcommand(1, 1);
	CLI11_PARSE(app, argc, argv);
	return 0;
} catch (const std::system_error& e) {
	std::cerr << e.what() << " (ec=" << e.code().value() << ")\n";
	return -1;
}
