#ifndef BIA_INTERNAL_TYPE_FUNCTION_HPP_
#define BIA_INTERNAL_TYPE_FUNCTION_HPP_

#include "definition.hpp"

#include <bia/util/type_traits/int_maker.hpp>
#include <tuple>
#include <type_traits>

namespace bia {
namespace internal {
namespace type {

struct Argument
{
	const Definition_base* definition;
};

class Definition_invokable_base : virtual public Definition_base
{
public:
	virtual const Definition_base* return_type() const noexcept = 0;
	virtual std::size_t arguments_size() const noexcept         = 0;
	virtual const Argument* arguments_begin() const noexcept    = 0;
	virtual const Argument* arguments_end() const noexcept      = 0;
};

template<typename Return, typename... Arguments>
class Definition_invokable_helper : public Definition_invokable_base, public Definition_real_base
{
public:
	Definition_invokable_helper(const std::type_info& info) noexcept : _index{ info }
	{
		_fill_arguments(util::type_traits::Int_sequencer<std::size_t, 0, sizeof...(Arguments)>::value);
	}
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
			n              = _return_type.compare(ptr->return_type());
			// compare arguments
			if (n == 0) {
				n = util::compare(arguments_size(), ptr->arguments_size());
				if (n == 0) {
					for (auto i = arguments_begin(), j = ptr->arguments_begin(); i != arguments_end() && n == 0; ++i) {
						n = i->definition->compare(j->definition);
					}
				}
			}
		}
		return n;
	}
	const Definition_base* return_type() const noexcept override
	{
		return &_return_type;
	}
	std::size_t arguments_size() const noexcept final
	{
		return sizeof...(Arguments);
	}
	const Argument* arguments_begin() const noexcept final
	{
		return _arguments;
	}
	const Argument* arguments_end() const noexcept final
	{
		return _arguments + sizeof...(Arguments);
	}
	const std::type_index& type_index() const noexcept override
	{
		return _index;
	}

private:
	Definition<typename std::decay<Return>::type> _return_type;
	std::tuple<Definition<typename std::decay<Arguments>::type>...> _argument_definitions;
	Argument _arguments[sizeof...(Arguments)];
	std::type_index _index;

	void _fill_arguments(util::type_traits::Int_container<std::size_t>) noexcept
	{}
	template<std::size_t Index, std::size_t... Indices>
	void _fill_arguments(util::type_traits::Int_container<std::size_t, Index, Indices...>) noexcept
	{
		_arguments[Index] = { &std::get<Index>(_argument_definitions) };
		_fill_arguments(util::type_traits::Int_container<std::size_t, Indices...>{});
	}
};

template<typename Return, typename... Arguments>
class Definition<Return(Arguments...)> : public Definition_invokable_helper<Return, Arguments...>
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
class Definition<Return (*)(Arguments...)> : public Definition_invokable_helper<Return, Arguments...>
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
class Definition<Return (Class::*)(Arguments...)> : public Definition_invokable_helper<Return, Arguments...>
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
class Definition<Return (Class::*)(Arguments...) const>
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
