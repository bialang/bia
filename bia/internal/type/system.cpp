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
    : _allocator{ allocator.get() }, _type_index{ allocator }
{
	// introduce real types
	_real_types[{ typeid(void) }] = get_or_create<Void>();

	_real_types[{ typeid(std::int8_t) }]   = get_or_create<Integer>(Integer::Size::i8, false);
	_real_types[{ typeid(std::uint8_t) }]  = get_or_create<Integer>(Integer::Size::u8, false);
	_real_types[{ typeid(std::int16_t) }]  = get_or_create<Integer>(Integer::Size::i16, false);
	_real_types[{ typeid(std::uint16_t) }] = get_or_create<Integer>(Integer::Size::u16, false);
	_real_types[{ typeid(std::int32_t) }]  = get_or_create<Integer>(Integer::Size::i32, true);
	_real_types[{ typeid(std::uint32_t) }] = get_or_create<Integer>(Integer::Size::u32, true);
	_real_types[{ typeid(std::int64_t) }]  = get_or_create<Integer>(Integer::Size::i64, false);
	_real_types[{ typeid(std::uint64_t) }] = get_or_create<Integer>(Integer::Size::u64, false);

	_real_types[{ typeid(float) }]  = get_or_create<Floating_point>(Floating_point::Size::f32);
	_real_types[{ typeid(double) }] = get_or_create<Floating_point>(Floating_point::Size::f64);

	_real_types[{ typeid(std::string) }] = get_or_create<String>();
	_real_types[{ typeid(std::regex) }]  = get_or_create<Regex>();

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

System::System(System&& move) noexcept
    : _allocator{ move._allocator }, _type_index{ std::move(move._type_index) }
{
	std::swap(_id_counter, move._id_counter);
}

System::~System() noexcept
{
	for (const auto& i : _type_index) {
		_allocator->destroy(const_cast<type::Definition*>(i.first));
	}
}

const Definition* System::definition_of(const std::type_info& type) const
{
	const auto it = _real_types.find({ type });
	if (it != _real_types.end()) {
		return it->second;
	}
	return nullptr;
}

System& System::operator=(System&& move) noexcept
{
	this->~System();
	new (this) System{ std::move(move) };
	return *this;
}
