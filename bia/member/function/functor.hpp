#ifndef BIA_MEMBER_FUNCTION_LAMBDA_HPP_
#define BIA_MEMBER_FUNCTION_LAMBDA_HPP_

#include "base.hpp"

#include <bia/util/type_traits/int_maker.hpp>
#include <bia/util/type_traits/invokable_info.hpp>
#include <type_traits>
#include <utility>

namespace bia {
namespace member {
namespace function {

template<typename Class, typename Return, typename... Arguments, std::size_t... Indices>
inline void invoke_method(Return (Class::*method)(Arguments...), Class& object, memory::Frame& frame,
                          util::type_traits::Int_container<std::size_t, Indices...>)
{
	frame.store(0, (object.*method)(frame.load_parameter<Indices, Arguments...>()...));
}

template<typename Class, typename Return, typename... Arguments, std::size_t... Indices>
inline void invoke_method(Return (Class::*method)(Arguments...) const, const Class& object,
                          memory::Frame& frame, util::type_traits::Int_container<std::size_t, Indices...>)
{
	frame.store(0, (object.*method)(frame.load_parameter<Indices, Arguments...>()...));
}

template<typename Class, typename... Arguments, std::size_t... Indices>
inline void invoke_method(void (Class::*method)(Arguments...), Class& object, memory::Frame& frame,
                          util::type_traits::Int_container<std::size_t, Indices...>)
{
	(object.*method)(frame.load_parameter<Indices, Arguments...>()...);
}

template<typename Class, typename... Arguments, std::size_t... Indices>
inline void invoke_method(void (Class::*method)(Arguments...) const, const Class& object,
                          memory::Frame& frame, util::type_traits::Int_container<std::size_t, Indices...>)
{
	(object.*method)(frame.load_parameter<Indices, Arguments...>()...);
}

template<typename Type>
class Functor : public Base
{
public:
	Functor(const Type& functor) : _functor{ functor }
	{}
	Functor(Type&& functor) : _functor{ std::move(functor) }
	{}
	void invoke(memory::Frame frame) override
	{
		invoke_method(
		  &Type::operator(), _functor, frame,
		  util::type_traits::Int_sequencer<std::size_t, 0,
		                                   util::type_traits::Invokable_info<Type>::argument_count>::value);
	}

private:
	Type _functor;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
