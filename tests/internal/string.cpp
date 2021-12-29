#define CATCH_CONFIG_MAIN

#include <bia/internal/string_key.hpp>
#include <bia/memory/simple_allocator.hpp>
#include <bia/resource/manager.hpp>
#include <bia/util/gsl.hpp>
#include <catch2/catch.hpp>

using namespace bia;

inline resource::View make_view(resource::Manager& manager, const char* value)
{
	auto mem = manager.start_memory(false);
	std::ostream output{ &mem };
	output.write(value, std::char_traits<char>::length(value) + 1);
	return mem.finish(resource::Type::string);
}

TEST_CASE("string key", "[internal]")
{
	resource::Manager manager{ std::make_shared<memory::Simple_allocator>() };
	const auto hi = make_view(manager, "hi");
	const auto ih = make_view(manager, "ih");

	const auto do_compares = [&](internal::String_key key) {
		INFO("Doing tests with key of type index " << key.index());

		REQUIRE(internal::compare(key, std::string{ "hi" }) == 0);
		REQUIRE(internal::compare(key, util::from_cstring("hi")) == 0);
		REQUIRE(internal::compare(key, hi) == 0);
		REQUIRE(internal::compare(key, std::string{ "ih" }) < 0);
		REQUIRE(internal::compare(key, util::from_cstring("ih")) < 0);
		REQUIRE(internal::compare(key, ih) < 0);
		REQUIRE(internal::compare(key, std::string{ "h" }) > 0);

		REQUIRE(internal::compare(std::string{ "hi" }, key) == 0);
		REQUIRE(internal::compare(util::from_cstring("hi"), key) == 0);
		REQUIRE(internal::compare(hi, key) == 0);
		REQUIRE(internal::compare(std::string{ "ih" }, key) > 0);
		REQUIRE(internal::compare(util::from_cstring("ih"), key) > 0);
		REQUIRE(internal::compare(ih, key) > 0);
		REQUIRE(internal::compare(std::string{ "h" }, key) < 0);
	};

	do_compares(std::string{ "hi" });
	do_compares(hi);
	do_compares(util::from_cstring("hi"));
}
