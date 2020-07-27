#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <bia/cbia.h>
#include <bia/connector/parameters.hpp>

bia_engine_t bia_engine_new()
try {
	return new bia::engine{};
} catch (...) {
	return nullptr;
}

void bia_engine_free(bia_engine_t engine)
try {
	delete static_cast<bia::engine*>(engine);
} catch (...) {
}

int bia_engine_put_function(bia_engine_t engine, const char* name, bia_function_t function, void* custom_arg)
try {
	if (!engine || !name || !function) {
		return -1;
	}

	static_cast<bia::engine*>(engine)->function(
	    name, [function, custom_arg](bia::parameters params) { function(&params, custom_arg); });

	return 0;
} catch (...) {
	return -1;
}

int bia_engine_use_bsl(bia_engine_t engine)
try {
	if (!engine) {
		return -1;
	}

	auto& eng = *static_cast<bia::engine*>(engine);

	eng.module<bia::bsl::io>("io", eng.gc());

	return 0;
} catch (...) {
	return -1;
}

int bia_run(bia_engine_t engine, const void* code, size_t length)
try {
	if (!engine || (!code && length)) {
		return -1;
	}

	/*struct membuf : std::streambuf
	{
	    membuf(char* begin, char* end)
	    {
	        setg(begin, begin, end);
	    }
	};

	membuf buffer{ static_cast<char*>(const_cast<void*>(code)),
	               static_cast<char*>(const_cast<void*>(code)) + length };
	std::istream istream{ &buffer };*/
	std::stringstream istream;
	istream.write(static_cast<const char*>(code), length);
	static_cast<bia::engine*>(engine)->execute(istream);

	return 0;
} catch (...) {
	return -1;
}
