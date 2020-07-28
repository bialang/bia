#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <bia/cbia.h>
#include <bia/connector/parameters.hpp>
#include <type_traits>

typedef typename std::remove_reference<bia::parameters>::type parameters_t;

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
		return berr_invalid_arguments;
	}

	static_cast<bia::engine*>(engine)->function(
	    name, [function, custom_arg](bia::parameters params) { function(&params, custom_arg); });

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_engine_use_bsl(bia_engine_t engine, const char* const* argv, size_t argc)
try {
	if (!engine) {
		return berr_invalid_arguments;
	}

	auto& eng = *static_cast<bia::engine*>(engine);

	eng.module<bia::bsl::io>("io", eng.gc());

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_run(bia_engine_t engine, const void* code, size_t length)
try {
	if (!engine || (!code && length)) {
		return berr_invalid_arguments;
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

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_parameters_count(bia_parameters_t params, size_t* out)
try {
	if (!params || !out) {
		return berr_invalid_arguments;
	}

	*out = static_cast<parameters_t*>(params)->size();

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_parameters_at(bia_parameters_t params, size_t index, bia_member_t* out)
try {
	if (!params || !out) {
		return berr_invalid_arguments;
	}

	*out = static_cast<parameters_t*>(params)->at(index);

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_parameters_positionals_count(bia_parameters_t params, size_t* out)
try {
	if (!params || !out) {
		return berr_invalid_arguments;
	}

	*out = static_cast<parameters_t*>(params)->positionals().size();

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_parameters_positionals_at(bia_parameters_t params, size_t index, bia_member_t* out)
try {
	if (!params || !out) {
		return berr_invalid_arguments;
	}

	*out = static_cast<parameters_t*>(params)->positionals().at(index);

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_parameters_kwargs_count(bia_parameters_t params, size_t* out)
try {
	if (!params || !out) {
		return berr_invalid_arguments;
	}

	*out = static_cast<parameters_t*>(params)->kwargs().size();

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_parameters_kwargs_at(bia_parameters_t params, size_t index, bia_member_t* out)
try {
	if (!params || !out) {
		return berr_invalid_arguments;
	}

	*out = static_cast<parameters_t*>(params)->kwargs().at(index);

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_parameters_kwargs_find(bia_parameters_t params, const char* name, bia_member_t* out)
try {
	if (!params || !name || !out) {
		return berr_invalid_arguments;
	}

	bool found;

	std::tie(*out, found) = (*static_cast<parameters_t*>(params))[name];

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_member_cast_int(bia_member_t member, int* out)
try {
	if (!member || !out) {
		return berr_invalid_arguments;
	}

	*out = bia::member::cast::cast<int>(*static_cast<bia::member::member*>(member));

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_member_cast_llong(bia_member_t member, long long* out)
try {
	if (!member || !out) {
		return berr_invalid_arguments;
	}

	*out = bia::member::cast::cast<long long>(*static_cast<bia::member::member*>(member));

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_member_cast_double(bia_member_t member, double* out)
try {
	if (!member || !out) {
		return berr_invalid_arguments;
	}

	*out = bia::member::cast::cast<double>(*static_cast<bia::member::member*>(member));

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}

int bia_member_cast_cstring(bia_member_t member, const char** out)
try {
	if (!member || !out) {
		return berr_invalid_arguments;
	}

	*out = bia::member::cast::cast<const char*>(*static_cast<bia::member::member*>(member));

	return berr_ok;
} catch (...) {
	return berr_invalid_arguments;
}
