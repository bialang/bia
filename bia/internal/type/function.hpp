#ifndef BIA_INTERNAL_TYPE_FUNCTION_HPP_
#define BIA_INTERNAL_TYPE_FUNCTION_HPP_

#include "definition.hpp"

#include <array>
#include <bia/util/gsl.hpp>
#include <bia/util/optional.hpp>
#include <bia/util/type_traits/is_varargs_invokable.hpp>
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <vector>

namespace bia {
namespace member {
namespace function {
template<typename Type>
class Varargs;
}
} // namespace member
namespace internal {
namespace type {

template<typename Type>
class Definition<member::function::Varargs<Type>> : public Definition<Type>
{};

struct Argument
{
	const Definition_base* definition;
};

class Definition_invokable_base : virtual public Definition_base
{
public:
	bool is_assignable(const Definition_base* other) const noexcept override
	{
		return compare(other) == 0;
	}
	std::size_t size() const noexcept override
	{
		return sizeof(void*);
	}
	std::size_t alignment() const noexcept override
	{
		return 1;
	}
	int flags() const noexcept override
	{
		return 0;
	}
	int compare(util::Not_null<const Definition_base*> other) const noexcept override
	{
		int n = util::compare(ordinal(), other->ordinal());
		if (n == 0) {
			const auto ptr = dynamic_cast<const Definition_invokable_base*>(other.get());
			// compare arguments
			if ((n = return_type()->compare(ptr->return_type())) == 0) {
				if ((n = util::compare(argument_lower_count(), ptr->argument_lower_count())) == 0) {
					n = util::compare(argument_upper_count(), ptr->argument_upper_count());
					for (auto i = arguments_begin(), j = ptr->arguments_begin(); n == 0 && i != arguments_end(); ++i) {
						n = i->definition->compare(j->definition);
					}
				}
			}
		}
		return n;
	}
	virtual const Definition_base* return_type() const noexcept           = 0;
	virtual bool is_vararg_index(std::size_t index) const noexcept        = 0;
	virtual std::size_t argument_lower_count() const noexcept             = 0;
	virtual std::size_t argument_upper_count() const noexcept             = 0;
	virtual const Argument* argument_at(std::size_t index) const noexcept = 0;
	virtual const Argument* arguments_begin() const noexcept              = 0;
	virtual const Argument* arguments_end() const noexcept                = 0;
};

struct Dynamic_function_signature
{
	util::Not_null<const Definition_base*> return_definition;
	std::vector<Argument> argument_definitions;
	util::Optional<Argument> vararg_definition;
};

struct Dynamic_function
{};

template<>
class Definition<Dynamic_function> : public Definition_invokable_base
{
public:
	Definition(Dynamic_function_signature signature) : _signature{ std::move(signature) }
	{
		if (_signature.vararg_definition.has_value()) {
			_signature.argument_definitions.push_back(*_signature.vararg_definition);
		}
	}
	unsigned int ordinal() const noexcept override
	{
		return 59;
	}
	const Definition_base* return_type() const noexcept override
	{
		return _signature.return_definition;
	}
	bool is_vararg_index(std::size_t index) const noexcept override
	{
		return _signature.vararg_definition.has_value() && index == _signature.argument_definitions.size() - 1;
	}
	std::size_t argument_lower_count() const noexcept override
	{
		return _signature.argument_definitions.size() - (_signature.vararg_definition.has_value() ? 1 : 0);
	}
	std::size_t argument_upper_count() const noexcept override
	{
		return _signature.vararg_definition.has_value() ? std::numeric_limits<std::size_t>::max()
		                                                : _signature.argument_definitions.size();
	}
	const Argument* argument_at(std::size_t index) const noexcept override
	{
		if (index < _signature.argument_definitions.size()) {
			return &_signature.argument_definitions[index];
		} else if (_signature.vararg_definition.has_value()) {
			return &_signature.argument_definitions.back();
		}
		return nullptr;
	}
	const Argument* arguments_begin() const noexcept final
	{
		return _signature.argument_definitions.empty() ? nullptr : &_signature.argument_definitions.front();
	}
	const Argument* arguments_end() const noexcept final
	{
		return _signature.argument_definitions.empty() ? nullptr : &_signature.argument_definitions.back() + 1;
	}

private:
	Dynamic_function_signature _signature;
};

template<typename Return, typename... Arguments>
class Definition_invokable_helper : public Definition_invokable_base, public Definition_real_base
{
public:
	constexpr static bool is_varargs = util::type_traits::Is_varargs_compatible_container<
	  util::type_traits::type_container<Arguments...>>::value;

	Definition_invokable_helper(const std::type_info& info) noexcept : _index{ info }
	{
		_fill_arguments<0, Arguments...>();
	}
	Definition_invokable_helper(const Definition_invokable_helper& copy) noexcept : _index{ copy._index }
	{
		_fill_arguments<0, Arguments...>();
	}
	~Definition_invokable_helper() noexcept = default;
	const Definition_base* return_type() const noexcept override
	{
		return &_return_type;
	}
	bool is_vararg_index(std::size_t index) const noexcept override
	{
		return is_varargs && index == sizeof...(Arguments) - 1;
	}
	std::size_t argument_lower_count() const noexcept override
	{
		return is_varargs ? sizeof...(Arguments) - 1 : sizeof...(Arguments);
	}
	std::size_t argument_upper_count() const noexcept override
	{
		return is_varargs ? std::numeric_limits<std::size_t>::max() : sizeof...(Arguments);
	}
	const Argument* argument_at(std::size_t index) const noexcept override
	{
		if (index < _arguments.size()) {
			return &_arguments[index];
		} else if (is_varargs) {
			return &_arguments.back();
		}
		return nullptr;
	}
	const Argument* arguments_begin() const noexcept final
	{
		return _arguments.begin();
	}
	const Argument* arguments_end() const noexcept final
	{
		return _arguments.end();
	}
	const std::type_index& type_index() const noexcept override
	{
		return _index;
	}
	Definition_invokable_helper& operator=(const Definition_invokable_helper& copy) noexcept
	{
		_index = copy._index;
		return *this;
	}

private:
	Definition<typename std::decay<Return>::type> _return_type;
	std::tuple<Definition<typename std::decay<Arguments>::type>...> _argument_definitions;
	std::array<Argument, sizeof...(Arguments)> _arguments{};
	std::type_index _index;

	template<std::size_t Index>
	void _fill_arguments() noexcept
	{}
	template<std::size_t Index, typename, typename... Others>
	void _fill_arguments() noexcept
	{
		_arguments[Index].definition = &std::get<Index>(_argument_definitions);
		_fill_arguments<Index + 1, Others...>();
	}
};

template<typename Return, typename... Arguments>
class Definition<Return(Arguments...), void> : public Definition_invokable_helper<Return, Arguments...>
{
public:
	Definition() noexcept : Definition_invokable_helper<Return, Arguments...>{ typeid(Return(Arguments...)) }
	{}
	unsigned int ordinal() const noexcept override
	{
		return 60;
	}
};

template<typename Return, typename... Arguments>
class Definition<Return (*)(Arguments...), void> : public Definition_invokable_helper<Return, Arguments...>
{
public:
	Definition() noexcept : Definition_invokable_helper<Return, Arguments...>{ typeid(Return(*)(Arguments...)) }
	{}
	unsigned int ordinal() const noexcept override
	{
		return 61;
	}
};

template<typename Class, typename Return, typename... Arguments>
class Definition<Return (Class::*)(Arguments...), void>
    : public Definition_invokable_helper<Return, Arguments...>
{
public:
	Definition() noexcept
	    : Definition_invokable_helper<Return, Arguments...>{ typeid(Return(Class::*)(Arguments...)) }
	{}
	unsigned int ordinal() const noexcept override
	{
		return 62;
	}
};

template<typename Class, typename Return, typename... Arguments>
class Definition<Return (Class::*)(Arguments...) const, void>
    : public Definition_invokable_helper<Return, Arguments...>
{
public:
	Definition() noexcept
	    : Definition_invokable_helper<Return, Arguments...>{ typeid(Return(Class::*)(Arguments...) const) }
	{}
	unsigned int ordinal() const noexcept override
	{
		return 63;
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
