#ifndef BIA_BYTECODE_WRITER_COMMON_HPP_
#define BIA_BYTECODE_WRITER_COMMON_HPP_

#include "../op_code.hpp"

#include <cstdint>
#include <ostream>
#include <type_traits>
#include <util/limit_checker.hpp>
#include <util/portable/stream.hpp>
#include <util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {
namespace writer {

template<typename T>
using is_int_immediate =
    util::type_traits::equals_any_type<typename std::decay<T>::type, std::int8_t, std::int16_t, std::int32_t>;

template<bool Optimize, typename T>
inline typename std::enable_if<
    util::type_traits::equals_any_type<typename std::decay<T>::type, op_code, std::int8_t, std::int16_t,
                                       std::int32_t, std::int64_t, std::uint8_t, std::uint16_t,
                                       std::uint32_t>::value != 0>::type
    optimized_write(std::ostream& output, T value)
{
	typedef typename std::decay<T>::type type;

	if (Optimize && !std::is_same<type, op_code>::value) {
		if (std::is_unsigned<type>::value) {
			if (util::limit_checker<std::uint8_t>::in_bounds(value)) {
				util::portable::write(output, static_cast<std::uint8_t>(value));
			} else if (util::limit_checker<std::uint16_t>::in_bounds(value)) {
				util::portable::write(output, static_cast<std::uint16_t>(value));
			} else {
				util::portable::write(output, value);
			}
		} else {
			if (util::limit_checker<std::int8_t>::in_bounds(value)) {
				util::portable::write(output, static_cast<std::int8_t>(value));
			} else if (util::limit_checker<std::int16_t>::in_bounds(value)) {
				util::portable::write(output, static_cast<std::int16_t>(value));
			} else if (util::limit_checker<std::int32_t>::in_bounds(value)) {
				util::portable::write(output, static_cast<std::int32_t>(value));
			} else {
				util::portable::write(output, value);
			}
		}
	} // don't optimize
	else {
		util::portable::write(output, value);
	}
}

} // namespace writer
} // namespace bytecode
} // namespace bia

#endif