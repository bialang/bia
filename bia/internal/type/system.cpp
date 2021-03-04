#include "system.hpp"

#include "floating_point.hpp"
#include "integer.hpp"
#include "regex.hpp"
#include "string.hpp"
#include "trivial.hpp"
#include "void.hpp"

#include <limits>
#include <regex>
#include <string>

using namespace bia::internal::type;

System::System(util::Not_null<std::shared_ptr<memory::Allocator>> allocator)
    : _allocator{ allocator.get() }, _types{ allocator }
{
	// introduce real types
	_real_types[{ typeid(void) }] = create_type<Void>();

	_real_types[{ typeid(std::int8_t) }]   = create_type<Integer>(Integer::Size::i8, false);
	_real_types[{ typeid(std::uint8_t) }]  = create_type<Integer>(Integer::Size::u8, false);
	_real_types[{ typeid(std::int16_t) }]  = create_type<Integer>(Integer::Size::i16, false);
	_real_types[{ typeid(std::uint16_t) }] = create_type<Integer>(Integer::Size::u16, false);
	_real_types[{ typeid(std::int32_t) }]  = create_type<Integer>(Integer::Size::i32, false);
	_real_types[{ typeid(std::uint32_t) }] = create_type<Integer>(Integer::Size::u32, false);
	_real_types[{ typeid(std::int64_t) }]  = create_type<Integer>(Integer::Size::i64, false);
	_real_types[{ typeid(std::uint64_t) }] = create_type<Integer>(Integer::Size::u64, false);

	_real_types[{ typeid(float) }]  = create_type<Floating_point>(Floating_point::Size::f32);
	_real_types[{ typeid(double) }] = create_type<Floating_point>(Floating_point::Size::f64);

	_real_types[{ typeid(std::string) }] = create_type<String>();
	_real_types[{ typeid(std::regex) }]  = create_type<Regex>();

	// create_type<Trivial<bool>>();
	// create_type<Trivial<char>>();
	// create_type<Trivial<char16_t>>();
	// create_type<Trivial<char32_t>>();
	// create_type<Trivial<wchar_t>>();
	// create_type<Trivial<signed char>>();
	// create_type<Trivial<unsigned char>>();
	// create_type<Trivial<signed short>>();
	// create_type<Trivial<unsigned short>>();
	// create_type<Trivial<signed int>>();
	// create_type<Trivial<unsigned int>>();
	// create_type<Trivial<signed long>>();
	// create_type<Trivial<unsigned long>>();
	// create_type<Trivial<signed long long>>();
	// create_type<Trivial<unsigned long long>>();

	// static_assert(std::numeric_limits<float>::is_iec559 && std::numeric_limits<float>::is_iec559 &&
	//                 std::numeric_limits<float>::is_iec559,
	//               "floating point IEC559 requried");
	// static_assert(sizeof(float) == 4, "float must be 32 bits wide");
	// static_assert(sizeof(double) == 8, "double must be 64 bits wide");
	// create_type<Trivial<float>>();
	// create_type<Trivial<double>>();
	// create_type<Trivial<long double>>();
}
