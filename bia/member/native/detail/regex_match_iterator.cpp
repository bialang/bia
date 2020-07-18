#include "regex_match_iterator.hpp"

#include "../../function/method.hpp"
#include "../string.hpp"
#include "regex_match.hpp"

using namespace bia::member::native::detail;

regex_match_iterator::regex_match_iterator(gc::object::immutable_pointer<char> string,
                                           gc::object::immutable_pointer<regex> pattern,
                                           std::cregex_iterator iterator)
    : _string{ string }, _pattern{ pattern }, _iterator{ std::move(iterator) }
{}

regex_match_iterator::flag_type regex_match_iterator::flags() const
{
	return flag_none;
}

regex_match_iterator::test_type regex_match_iterator::test(test_operator op, const member& right) const
{
	return _valid;
}

bia::gc::gcable<bia::member::member> regex_match_iterator::copy() const
{
	return gc::gc::active_gc()->construct<regex_match_iterator>(*this);
}

bia::gc::gcable<bia::member::member> regex_match_iterator::invoke(parameters_type params)
{
	if (_valid = _iterator != std::cregex_iterator{}) {
		auto result = gc::gc::active_gc()->construct<regex_match>(_string, *_iterator);

		++_iterator;

		return result;
	}

	return {};
}

bia::gc::gcable<bia::member::member> regex_match_iterator::operation(const member& right, infix_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex_match_iterator::self_operation(self_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex_match_iterator::get(const native::string& name)
{
	if (!name.compare("__iter__")) {
		return this;
	}

	return {};
}

regex_match_iterator::float_type regex_match_iterator::as_float() const noexcept
{
	return {};
}

regex_match_iterator::int_type regex_match_iterator::as_int() const noexcept
{
	return {};
}

bool regex_match_iterator::as_data(const std::type_info& type, void* output)
{
	return false;
}

bool regex_match_iterator::as_data(const std::type_info& type, void* output) const
{
	return false;
}

void regex_match_iterator::gc_mark_children(bool mark) const noexcept
{
	gc::object::gc_mark(_string.get(), mark);
	gc::object::gc_mark(_pattern.get(), mark);
}

void regex_match_iterator::register_gcables(gc::gc& gc) const noexcept
{
	gc.register_gcable(_string.get());
	gc.register_gcable(_pattern.get());
}
