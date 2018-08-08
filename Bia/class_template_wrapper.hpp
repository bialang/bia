#pragma once

#include <utility>

#include "class_template.hpp"
#include "static_function.hpp"
#include "lambda_function.hpp"
#include "member_function.hpp"
#include "string_manager.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _Ty>
class class_template_wrapper
{
public:
	class_template_wrapper(machine::machine_context & _context, class_template<_Ty> * _template) : _context(_context)
	{
		this->_template = _template;
	}
	template<typename... _Args>
	class_template_wrapper & set_constructor()
	{
		// Set the active allocator
		machine::machine_context::_active_allocator = _context.allocator();

		_template->set_constructor<_Args...>();

		return *this;
	}
	template<typename _Return, typename... _Args>
	class_template_wrapper & set_function(machine::string_manager::name_type _name, _Return(*_function)(_Args...))
	{
		// Set the active allocator
		machine::machine_context::_active_allocator = _context.allocator();

		_template->emplace_member<framework::executable::static_function<_Return, _Args...>>(_context.name_address(_name), _function);

		return *this;
	}
	template<typename _Class, typename _Return, typename... _Args>
	class_template_wrapper & set_function(machine::string_manager::name_type _name, _Return(_Class::*_function)(_Args...))
	{
		// Set the active allocator
		machine::machine_context::_active_allocator = _context.allocator();

		_template->emplace_member<framework::executable::member_function<_Return(_Class::*)(_Args...)>>(_context.name_address(_name), _function);

		return *this;
	}
	template<typename _Lambda>
	class_template_wrapper & set_lambda(machine::string_manager::name_type _name, _Lambda && _lambda)
	{
		// Set the active allocator
		machine::machine_context::_active_allocator = _context.allocator();

		_template->emplace_member<framework::executable::lambda_function<typename std::remove_cv<typename std::remove_reference<_Lambda>::type>::type>>(_context.name_address(_name), std::forward<_Lambda>(_lambda));

		return *this;
	}

	//template<typename _Class>
	//class_template_wrapper & set_class(machine::string_manager::name_type _name)
	//{
	//	// Set the active allocator
	//	machine::machine_context::_active_allocator = _context.allocator();

	//	_context.emplace_member<framework::object::class_template<_Class>>(_name);
	//}

private:
	machine::machine_context & _context;
	class_template<_Ty> * _template;
};

}
}
}