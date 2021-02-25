#include "system.hpp"

#include "floating_point.hpp"
#include "integer.hpp"
#include "regex.hpp"
#include "string.hpp"
#include "void.hpp"

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
	_real_types[{ typeid(std::regex) }] = create_type<Regex>();
}
