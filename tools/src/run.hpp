#ifndef BIA_TOOL_RUN_HPP_
#define BIA_TOOL_RUN_HPP_

#include "error.hpp"

#include <CLI/CLI.hpp>
#include <bia/bia.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class run
{
public:
	run(CLI::App& app)
	{
		auto cmd = app.add_subcommand("run", "run a given source file");
		cmd->add_option("source", _filename, "the source file; use '-' for stdin")
		    ->required()
		    ->check([](const std::string& filename) {
			    return filename == "-" ? "" : CLI::ExistingFile(filename);
		    });
		cmd->add_option("args", _args, "the remaining arguments that are passed to the script");
		cmd->add_flag("--no-bsl", _no_bsl, "disable the use of the standard library");
		cmd->add_flag("--no-bel", _no_bel, "disable the use of the extended library");
		cmd->callback(std::bind(&run::_process, this));
	}

private:
	bool _no_bsl = false;
	bool _no_bel = false;
	std::string _filename;
	std::vector<std::string> _args;

	void _process()
	{
		std::vector<const char*> arg_ptrs;
		arg_ptrs.reserve(_args.size());
		for (const auto& i : _args) {
			arg_ptrs.push_back(i.c_str());
		}

		bia::engine engine;
		if (!_no_bsl) {
			engine.use_bsl({ arg_ptrs.data(), arg_ptrs.data() + arg_ptrs.size() });
		}

		std::istream* input = nullptr;
		std::ifstream file;
		if (_filename == "-") {
			input = &std::cin;
		} else {
			file.open(_filename, std::ios::in | std::ios::binary);
			if (!file.is_open()) {
				throw std::system_error{ errc::file_not_found, _filename };
			}
			input = &file;
		}
		engine.execute(*input);
	}
};

#endif
