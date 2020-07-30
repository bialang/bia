#include "regex_match.hpp"

#include "../../function/method.hpp"
#include "../string.hpp"

#include <bia/connector/connector-inl.hpp>

using namespace bia::member::native::detail;

regex_match::regex_match(gc::object::immutable_pointer<char> string, std::cmatch match)
    : _string{ string }, _match{ std::move(match) }
{}

regex_match::flag_type regex_match::flags() const
{
	return flag_none;
}

regex_match::test_type regex_match::test(test_operator op, const member& right) const
{
	return _match.ready();
}

bia::gc::gcable<bia::member::member> regex_match::copy() const
{
	return gc::gc::active_gc()->construct<regex_match>(*this);
}

bia::gc::gcable<bia::member::member> regex_match::invoke(parameters_type params, invoke_context& context)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex_match::operation(const member& right, infix_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex_match::self_operation(self_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> regex_match::get(const native::string& name)
{
	if (!name.compare("group")) {
		return gc::gc::active_gc()
		    ->template construct<function::method<true, decltype(&regex_match::_group)>>(
		        *this, &regex_match::_group);
	}

	return {};
}

regex_match::float_type regex_match::as_float() const noexcept
{
	return {};
}

regex_match::int_type regex_match::as_int() const noexcept
{
	return {};
}

bool regex_match::as_data(const std::type_info& type, void* output)
{
	return false;
}

bool regex_match::as_data(const std::type_info& type, void* output) const
{
	return false;
}

void regex_match::gc_mark_children(bool mark) const noexcept
{
	gc::object::gc_mark(_string.get(), mark);
}

void regex_match::register_gcables(gc::gc& gc) const noexcept
{
	gc.register_gcable(_string.get());
}

bia::gc::gcable<bia::member::native::string> regex_match::_group(std::size_t index) const
{
	if (index >= _match.size()) {
		return {};
	}

	const auto sub_match = _match[index];
	const auto gc        = gc::gc::active_gc();
	const auto mem       = static_cast<char*>(gc->allocate(sub_match.length() + 1).release());

	std::memcpy(mem, sub_match.first, sub_match.length());

	mem[sub_match.length()] = 0;

	return gc->template construct<string>(mem);
}
