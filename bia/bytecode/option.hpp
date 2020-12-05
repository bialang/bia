#ifndef BIA_BYTECODE_DETAIL_OPTION_HPP_
#define BIA_BYTECODE_DETAIL_OPTION_HPP_

#include <cstddef>

namespace bia {
namespace bytecode {

enum member_destination_option
{
	mdo_args_16,
	mdo_global_16,
	mdo_local_16,
	mdo_args_8,
	mdo_global_8,
	mdo_local_8,
	mdo_push,

	mdo_count = 8
};

enum member_source_option
{
	mso_args_16,
	mso_global_16,
	mso_local_16,
	mso_resource_16,
	mso_args_8,
	mso_global_8,
	mso_local_8,
	mso_resource_8,
	mso_builtin,

	mso_count = 16
};

enum constant_option
{
	co_int_8,
	co_uint_8,
	co_int_16,
	co_uint_16,
	co_int_32,
	co_uint_32,
	co_int_64,
	co_uint_64,
	co_float_32,
	co_float_64,
	co_bool,
	co_test_register,
	co_null,

	co_count = 16
};

enum resource_option
{
	ro_8,
	ro_16,
	ro_24,
	ro_32,

	ro_count = 4
};

enum offset_option
{
	oo_8,
	oo_16,
	oo_24,
	oo_32,

	oo_count = 4
};

template<typename>
constexpr std::size_t bit_size();

template<>
constexpr std::size_t bit_size<member_destination_option>()
{
	return 3;
}

template<>
constexpr std::size_t bit_size<member_source_option>()
{
	return 4;
}

template<>
constexpr std::size_t bit_size<constant_option>()
{
	return 3;
}

template<>
constexpr std::size_t bit_size<resource_option>()
{
	return 2;
}

template<>
constexpr std::size_t bit_size<offset_option>()
{
	return 2;
}

} // namespace bytecode
} // namespace bia

#endif
