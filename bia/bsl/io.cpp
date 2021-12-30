#include "modules.hpp"

#include <bia/member/function/varargs.hpp>
#include <bia/util/variant.hpp>
#include <iostream>

template<std::size_t Index, typename Variant>
inline void do_print(const Variant& value)
{
	std::cout << "<empty>";
}

template<std::size_t Index, typename, typename... Others, typename Variant>
inline void do_print(const Variant& value)
{
	if (value.index() == Index) {
		std::cout << value.template get<Index>();
	} else {
		do_print<Index + 1, Others...>(value);
	}
}

void bia::bsl::io(internal::Typed_object& object)
{
	using Vararg = util::Variant<bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t,
	                             std::uint32_t, std::int64_t, std::uint64_t, float, double, std::string>;

	member::function::Signature signature{ object.type_system().definition_of<void>() };
	signature.vararg_definition = internal::type::Argument{ object.type_system().definition_of<Vararg>() };

	object.put_invokable(
	  util::from_cstring("print"),
	  [](member::function::Context& context) {
		  for (std::size_t i = 0; i < context.size(); ++i) {
			  do_print<0, bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t,
			           std::int64_t, std::uint64_t, float, double, std::string>(context.get_argument<Vararg>(i));
			  std::cout << " ";
		  }
		  std::cout << "\n";
	  },
	  std::move(signature));
}
