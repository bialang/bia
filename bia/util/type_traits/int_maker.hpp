#ifndef BIA_UTIL_TYPE_TRAITS_INT_MAKER_HPP_
#define BIA_UTIL_TYPE_TRAITS_INT_MAKER_HPP_

#include <cstdint>

namespace bia {
namespace util {
namespace type_traits {

template<typename Type, Type... Ints>
struct Int_container
{};

template<typename Type, std::size_t Count, Type Value, Type... Ints>
struct Int_filler : Int_filler<Type, Count - 1, Value, Ints..., Value>
{};

/// Starter.
template<typename Type, std::size_t Count, Type Value>
struct Int_filler<Type, Count, Value> : Int_filler<Type, Count - 1, Value, Value>
{
	constexpr static std::size_t count = Count;
};

/// Stopper.
template<typename Type, Type Value, Type... Ints>
struct Int_filler<Type, 0, Value, Ints...>
{
	constexpr static Int_container<Type, Ints...> value{};
};

template<typename Type, Type From, Type To, Type... Ints>
struct Int_sequencer : Int_sequencer<Type, From + 1, To, Ints..., From>
{};

/// Stopper.
template<typename Type, Type To, Type... Ints>
struct Int_sequencer<Type, To, To, Ints...>
{
	constexpr static Int_container<Type, Ints...> value{};
};

// template<typename Type, Type Stop>
// struct Int_sequencer<Type, Stop, Stop>
// {
// 	constexpr static std::size_t count = 0;
// 	constexpr static Int_container<Type> value{};
// };

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
