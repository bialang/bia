#ifndef BIA_UTIL_TYPE_TRAITS_INT_MAKER_HPP_
#define BIA_UTIL_TYPE_TRAITS_INT_MAKER_HPP_

#include <cstdint>

namespace bia {
namespace util {
namespace type_traits {

template<typename T, T... Ints>
struct int_container
{};

template<typename T, std::size_t Count, T Value, T... Ints>
struct int_filler : int_filler<T, Count - 1, Value, Ints..., Value>
{};

/* starter */
template<typename T, std::size_t Count, T Value>
struct int_filler<T, Count, Value> : int_filler<T, Count - 1, Value, Value>
{
	constexpr static auto count = Count;
	typedef T int_type;
};

/* stopper */
template<typename T, T Value, T... Ints>
struct int_filler<T, 0, Value, Ints...>
{
	constexpr static int_container<T, Ints...> value{};
};

template<typename T, T Counter, T Stop, T... Ints>
struct int_sequencer : int_sequencer<T, Counter + 1, Stop, Ints..., Counter>
{};

/* starter */
template<typename T, T Start, T Stop>
struct int_sequencer<T, Start, Stop> : int_sequencer<T, Start + 1, Stop, Start>
{
	constexpr static auto count = Stop - Start;
	typedef T int_type;
};

template<typename T, T Stop>
struct int_sequencer<T, Stop, Stop>
{
	constexpr static auto count = 0;
	constexpr static int_container<T> value{};
	typedef T int_type;
};

/* stopper */
template<typename T, T Stop, T... Ints>
struct int_sequencer<T, Stop, Stop, Ints...>
{
	constexpr static int_container<T, Ints...> value{};
};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif