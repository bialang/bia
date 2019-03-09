#pragma once

#include <utility>
#include <type_traits>

#include "class_template.hpp"
#include "static_function.hpp"
#include "lambda_function.hpp"
#include "member_function.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type, typename Class>
class template_wrapper
{
public:
	template_wrapper(machine::machine_context & _context, Type * _template_member) : _context(_context)
	{
		this->_template_member = _template_member;
	}
	template<typename... Arguments, bool Is_class = std::is_class<Class>::value>
	typename std::enable_if<Is_class, template_wrapper&>::type set_constructor()
	{
		// Set the active allocator
		_context.activate_context();

		_template_member->template set_constructor<Arguments...>();

		return *this;
	}
	template<typename Return, typename... Arguments>
	template_wrapper & set_function(member_map::name_t _name, Return(*_function)(Arguments...))
	{
		// Set the active allocator
		_context.activate_context();

		_template_member->members().template emplace<framework::executable::static_function<Return, Arguments...>>(_context.name_address(_name), _function);

		return *this;
	}
	template<typename Active_class = Class, typename Function_class, typename Return, typename... Arguments>
	typename std::enable_if<std::is_base_of<Function_class, Active_class>::value, template_wrapper&>::type  set_function(member_map::name_t _name, Return(Function_class::*_function)(Arguments...))
	{
		// Set the active allocator
		_context.activate_context();

		_template_member->members().template emplace<framework::executable::member_function<Return(Active_class::*)(Arguments...)>>(_context.name_address(_name), _function);

		return *this;
	}
	template<typename _Lambda>
	template_wrapper & set_lambda(member_map::name_t _name, _Lambda && _lambda)
	{
		// Set the active allocator
		_context.activate_context();

		_template_member->members().template emplace<framework::executable::lambda_function<typename std::remove_cv<typename std::remove_reference<_Lambda>::type>::type>>(_context.name_address(_name), std::forward<_Lambda>(_lambda));

		return *this;
	}
	/**
	 * Returns the member or creates it if needed.
	 *
	 * @since 3.68.140.788
	 * @date 16-Sep-18
	 *
	 * @param _name The name of the member.
	 *
	 * @throws See member_map::get_or_create().
	 *
	 * @return The member.
	*/
	member * member_address(member_map::name_t _name)
	{
		return _template_member->members().get_or_create(_context.name_address(_name));
	}

protected:
	/** The machine context. */
	machine::machine_context & _context;
	/** The template member with a member map. */
	Type * _template_member;
};

}
}
}
