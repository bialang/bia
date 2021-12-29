#define CATCH_CONFIG_MAIN

#include <bia/engine.hpp>
#include <catch2/catch.hpp>
#include <filesystem>
#include <fstream>
#include <memory>

inline std::unique_ptr<bia::Engine> create_engine()
{
	std::unique_ptr<bia::Engine> engine{ new bia::Engine{} };
	engine->function("require",
	                 [](std::ptrdiff_t actual, std::ptrdiff_t expected) { REQUIRE(actual == expected); });
	engine->function("fail", [] { FAIL(); });
	engine->variable("root_path", std::filesystem::path{ __FILE__ }.parent_path().string());
	return engine;
}

TEST_CASE("main")
{
	for (const auto& entry :
	     std::filesystem::directory_iterator{ std::filesystem::path{ __FILE__ }.parent_path() }) {
		if (entry.is_regular_file() && entry.path().extension() == ".bia") {
			std::ifstream file{ entry.path(), std::ios::in | std::ios::binary };
			INFO("Executing file: " << entry);
			REQUIRE(file.is_open());
			create_engine()->run(file);
		}
	}
}
