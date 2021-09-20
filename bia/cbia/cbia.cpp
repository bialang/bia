#include <bia/cbia.h>
#include <bia/engine.hpp>
#include <sstream>

using namespace bia;

bia_engine_t bia_engine_new()
try {
	return new Engine{};
} catch (...) {
	return nullptr;
}

void bia_engine_free(bia_engine_t engine)
try {
	delete static_cast<Engine*>(engine);
} catch (...) {
}

bia_err_t bia_engine_use_bsl(bia_engine_t engine)
try {
	static_cast<Engine*>(engine)->use_bsl();
	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}

bia_err_t bia_engine_put_function(bia_engine_t engine, const char* name, bia_signature_t signature,
                                  bia_function_t function, void* argument, bool immutable)
try {
	static_cast<Engine*>(engine)->function(
	  name, [function, argument](member::function::Context& context) { function(&context, argument); },
	  *static_cast<member::function::Signature*>(signature), immutable);
	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}

template<typename Type>
inline bia_err_t function_context_return(bia_function_context_t context, Type value)
try {
	static_cast<member::function::Context*>(context)->set_return(value);
	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}

bia_err_t bia_function_context_return_char(bia_function_context_t context, char value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_uchar(bia_function_context_t context, unsigned char value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_schar(bia_function_context_t context, signed char value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_short(bia_function_context_t context, short int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_ushort(bia_function_context_t context, unsigned short int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_int(bia_function_context_t context, int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_uint(bia_function_context_t context, unsigned int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_long(bia_function_context_t context, long int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_ulong(bia_function_context_t context, unsigned long int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_llong(bia_function_context_t context, long long int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_ullong(bia_function_context_t context, unsigned long long int value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_float(bia_function_context_t context, float value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_double(bia_function_context_t context, double value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_long_double(bia_function_context_t context, long double value)
{
	return function_context_return(context, value);
}

bia_err_t bia_function_context_return_string(bia_function_context_t context, const char* value)
{
	return function_context_return(context, std::string{ value });
}

template<typename Type>
inline bia_err_t function_context_get(bia_function_context_t context, size_t index, Type* out)
try {
	*out = static_cast<member::function::Context*>(context)->get_argument<Type>(index);
	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}

bia_err_t bia_function_context_get_char(bia_function_context_t context, size_t index, char* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_uchar(bia_function_context_t context, size_t index, unsigned char* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_schar(bia_function_context_t context, size_t index, signed char* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_short(bia_function_context_t context, size_t index, short int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_ushort(bia_function_context_t context, size_t index,
                                          unsigned short int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_int(bia_function_context_t context, size_t index, int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_uint(bia_function_context_t context, size_t index, unsigned int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_long(bia_function_context_t context, size_t index, long int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_ulong(bia_function_context_t context, size_t index, unsigned long int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_llong(bia_function_context_t context, size_t index, long long int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_ullong(bia_function_context_t context, size_t index,
                                          unsigned long long int* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_float(bia_function_context_t context, size_t index, float* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_double(bia_function_context_t context, size_t index, double* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_long_double(bia_function_context_t context, size_t index, long double* out)
{
	return function_context_get(context, index, out);
}

bia_err_t bia_function_context_get_string(bia_function_context_t context, size_t index, char** out)
try {
	const auto str = static_cast<member::function::Context*>(context)->get_argument<std::string>(index);
	*out           = static_cast<char*>(std::malloc(str.size() + 1));
	std::memcpy(*out, str.c_str(), str.size() + 1);
	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}

bia_definition_t bia_standard_definition(bia_engine_t engine, bia_standard_definition_t type)
try {
	auto& type_system = static_cast<Engine*>(engine)->context().global_namespace().type_system();
	switch (type) {
	case BIA_DEF_VOID: return type_system.definition_of<void>();
	case BIA_DEF_CHAR: return type_system.definition_of<char>();
	case BIA_DEF_UNSIGNED_CHAR: return type_system.definition_of<unsigned char>();
	case BIA_DEF_SIGNED_CHAR: return type_system.definition_of<signed char>();
	case BIA_DEF_SHORT_INT: return type_system.definition_of<short int>();
	case BIA_DEF_UNSIGNED_SHORT_INT: return type_system.definition_of<unsigned short int>();
	case BIA_DEF_INT: return type_system.definition_of<int>();
	case BIA_DEF_UNSIGNED_INT: return type_system.definition_of<unsigned int>();
	case BIA_DEF_LONG_INT: return type_system.definition_of<long int>();
	case BIA_DEF_UNSIGNED_LONG_INT: return type_system.definition_of<unsigned long int>();
	case BIA_DEF_LONG_LONG_INT: return type_system.definition_of<long long int>();
	case BIA_DEF_UNSIGNED_LONG_LONG_INT: return type_system.definition_of<unsigned long long int>();
	case BIA_DEF_FLOAT: return type_system.definition_of<float>();
	case BIA_DEF_DOUBLE: return type_system.definition_of<double>();
	case BIA_DEF_LONG_DOUBLE: return type_system.definition_of<long double>();
	case BIA_DEF_STRING: return type_system.definition_of<std::string>();
	}
	return nullptr;
} catch (...) {
	return nullptr;
}

bia_signature_t bia_signature_new(bia_definition_t return_definition, bia_definition_t vararg_definition)
try {
	const auto ptr =
	  new member::function::Signature{ static_cast<const internal::type::Definition_base*>(return_definition) };
	if (vararg_definition) {
		ptr->vararg_definition.emplace(static_cast<const internal::type::Definition_base*>(vararg_definition));
	}
	return ptr;
} catch (...) {
	return nullptr;
}

bia_err_t bia_signature_push_argument(bia_signature_t signature, bia_definition_t definition)
try {
	static_cast<member::function::Signature*>(signature)->argument_definitions.push_back(
	  { static_cast<const internal::type::Definition_base*>(definition) });
	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}

bia_err_t bia_run(bia_engine_t engine, const char* code, size_t size)
try {
	std::stringstream ss;
	ss.write(code, size);
	static_cast<Engine*>(engine)->run(ss);
	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}
