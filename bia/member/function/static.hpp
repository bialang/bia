#ifndef BIA_MEMBER_FUNCTION_STATIC_HPP_
#define BIA_MEMBER_FUNCTION_STATIC_HPP_

#include "base.hpp"

#include <bia/util/type_traits/int_maker.hpp>

namespace bia {
namespace member {
namespace function {

template<typename Return, typename... Arguments, std::size_t... Indices>
inline void invoke_static(Return (*function)(Arguments...), memory::Frame& frame,
                          util::type_traits::Int_container<std::size_t, Indices...>)
{
	function(frame.load<Arguments>(alignof(std::max_align_t) * Indices)...);
}

template<typename Return, typename... Arguments>
class Static : public Base
{
public:
	typedef Return (*Function)(Arguments...);

	Static(Function pointer) noexcept : _pointer{ pointer }
	{}
	void invoke(memory::Frame frame) override
	{
		invoke_static(_pointer, frame,
		              util::type_traits::Int_sequencer<std::size_t, 0, sizeof...(Arguments)>::value);
	}

private:
	Function _pointer;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
