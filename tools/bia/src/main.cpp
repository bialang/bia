#include <CLI/CLI.hpp>

int main(int argc, char** argv)
{
	CLI::App app("Bia command line tool used for executing, compiling, packaging and installing scripts/modules");

	app.allow_windows_style_options();

	app.set_help_all_flag("--help-all", "Expand help all");
	app.set_help_flag("-h,--help", "Expand quick help");

	auto compile = app.add_subcommand("compile", "Compiles a Bia script to a compiled script object");
	auto package = app.add_subcommand(
	    "package",
	    "Packages a list of files/directories into a BAG file which can then be used as a package of scripts");

	app.require_subcommand(0, 1);

	CLI11_PARSE(app, argc, argv);

	auto command = app.get_subcommands();

	// Execute
	if (command.empty()) {
	}

	return 0;
}