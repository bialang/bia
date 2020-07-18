#include "regex.hpp"

#include "../cast/cast.hpp"
#include "../function/method.hpp"
#include "detail/regex_match.hpp"
#include "detail/regex_match_iterator.hpp"
#include "string.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>

using namespace bia::member::native;

regex::regex(std::regex pattern) : _pattern{ std::move(pattern) }
{}

regex::flag_type regex::flags() const
{
	return flag_none;
}

regex::test_type regex::test(test_operator op, const member& right) const
{
	switch (op) {
	case test_operator::in: return std::regex_search(cast::cast<const char*>(right), _pattern);
	case test_operator::equal: return std::regex_match(cast::cast<const char*>(right), _pattern);
	case test_operator::not_equal: return !std::regex_match(cast::cast<const char*>(right), _pattern);
	default: return 0;
	}
}

bia::gc::gcable<bia::member::member> regex::copy() const
{
	return gc::gc::active_gc()->construct<regex>(*this);
}

bia::gc::gcable<bia::member::member> regex::invoke(parameters_type params)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex::operation(const member& right, infix_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex::self_operation(self_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex::get(const native::string& name)
{
	if (!name.compare("match")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&regex::_match)>>(
		    *this, &regex::_match);
	} else if (!name.compare("match_all")) {
		return gc::gc::active_gc()->construct<function::method<true, decltype(&regex::_match_all)>>(
		    *this, &regex::_match_all);
	} else if (!name.compare("search")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&regex::_search)>>(
		    *this, &regex::_search);
	} else if (!name.compare("name")) {
		return creator::create("std::regex");
	}

	return {};
}

regex::float_type regex::as_float() const noexcept
{
	return {};
}

regex::int_type regex::as_int() const noexcept
{
	return {};
}

bool regex::as_data(const std::type_info& type, void* output)
{
	return false;
}

bool regex::as_data(const std::type_info& type, void* output) const
{
	return false;
}

void regex::gc_mark_children(bool mark) const noexcept
{}

void regex::register_gcables(gc::gc& gc) const noexcept
{}

bia::gc::gcable<bia::member::member> regex::_match(connector::parameters_type params)
{
	std::cmatch match;

	if (!dynamic_cast<string*>(params[0])) {
		throw;
	}

	if (std::regex_match(cast::cast<const char*>(*params[0]), match, _pattern)) {
		return gc::gc::active_gc()->template construct<detail::regex_match>(
		    static_cast<string*>(params[0])->value(), match);
	}

	return {};
}

bia::gc::gcable<bia::member::member> regex::_search(connector::parameters_type params)
{
	std::cmatch match;

	if (!dynamic_cast<string*>(params[0])) {
		throw;
	}

	if (std::regex_search(cast::cast<const char*>(*params[0]), match, _pattern)) {
		return gc::gc::active_gc()->template construct<detail::regex_match>(
		    static_cast<string*>(params[0])->value(), match);
	}

	return {};
}

bia::gc::gcable<bia::member::member> regex::_match_all(connector::parameters_type params)
{
	if (!dynamic_cast<string*>(params[0])) {
		throw;
	}

	return gc::gc::active_gc()->construct<detail::regex_match_iterator>(
	    static_cast<string*>(params[0])->value(), this,
	    std::cregex_iterator{
	        static_cast<string*>(params[0])->value().get(),
	        static_cast<string*>(params[0])->value().get() +
	            std::char_traits<char>::length(static_cast<string*>(params[0])->value().get()),
	        _pattern });
}
