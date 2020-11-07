#ifndef BIA_TOOL_VERSION_HPP_
#define BIA_TOOL_VERSION_HPP_

#include "config.hpp"

#include <CLI/CLI.hpp>
#include <bia/bia.hpp>
#include <iostream>
#include <string>

class version
{
public:
	version(CLI::App& app)
	{
		auto cmd = app.add_subcommand("version", "prints the bia version");
		cmd->add_set("-f,--format", _format, { "pretty", "json" }, "the output format");
		cmd->callback(std::bind(&version::_process, this));
	}

private:
	std::string _format = "pretty";

	void _process()
	{
		if (_format == "pretty") {
			std::cout << "Bia: " << BIA_VERSION << "\nBia Tool: v" << BIA_TOOL_VERSION << '\n';
		} else if (_format == "json") {
			std::cout << R"({"bia":")" << BIA_VERSION << R"(","tool":")" << BIA_TOOL_VERSION << "\"}\n";
		}
	}
};

#endif
