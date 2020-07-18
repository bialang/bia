#include "string.hpp"

#include "../function/method.hpp"

#include <algorithm>
#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
#include <bia/gc/gc.hpp>
#include <bia/log/log.hpp>
#include <cctype>
#include <cstring>

using namespace bia::member::native;

string::string(gc::object::immutable_pointer<char> value) noexcept : _value(value)
{}

string::~string()
{
	BIA_LOG(DEBUG, "destroying string='{}': {}", _value.get(), static_cast<void*>(this));
}

string::flag_type string::flags() const
{
	return flag_none;
}

string::test_type string::test(test_operator op, const member& right) const
{
	return _value.get()[0] ? 1 : 0;
}

bia::gc::gcable<bia::member::member> string::copy() const
{
	return gc::gc::active_gc()->construct<string>(_value);
}

bia::gc::gcable<bia::member::member> string::invoke(parameters_type params)
{
	return {};
}

bia::gc::gcable<bia::member::member> string::operation(const member& right, infix_operator op)
{
	if (op == infix_operator::addition && dynamic_cast<const string*>(&right)) {
		const auto len0 = std::char_traits<char>::length(_value.get());
		const auto len1 = std::char_traits<char>::length(static_cast<const string*>(&right)->_value.get());
		auto mem        = gc::gc::active_gc()->allocate(len0 + len1 + 1);

		std::memcpy(mem.peek(), _value.get(), len0);
		std::memcpy(static_cast<char*>(mem.peek()) + len0, static_cast<const string*>(&right)->_value.get(),
		            len1);

		static_cast<char*>(mem.peek())[len0 + len1] = 0;

		return gc::gc::active_gc()->construct<string>(static_cast<char*>(mem.release()));
	}

	return {};
}

bia::gc::gcable<bia::member::member> string::self_operation(self_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> string::get(const native::string& name)
{
	if (!name.compare("lower")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&string::_lower)>>(
		    *this, &string::_lower);
	} else if (!name.compare("upper")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&string::_upper)>>(
		    *this, &string::_upper);
	} else if (!name.compare("length")) {
		return creator::create(std::char_traits<char>::length(_value.get()));
	}

	return {};
}

string::float_type string::as_float() const noexcept
{
	return {};
}

string::int_type string::as_int() const noexcept
{
	return {};
}

bool string::as_data(const std::type_info& type, void* output)
{
	return false;
}

bool string::as_data(const std::type_info& type, void* output) const
{
	if (type == typeid(const char*)) {
		*static_cast<const char**>(output) = _value.get();

		return true;
	}

	return false;
}

int string::compare(const string& other) const noexcept
{
	return std::strcmp(_value.get(), other._value.get());
}

int string::compare(util::czstring other) const noexcept
{
	return std::strcmp(_value.get(), other);
}

void string::gc_mark_children(bool mark) const noexcept
{
	gc::object::gc_mark(_value.get(), mark);
}

bia::gc::object::immutable_pointer<char> string::value() const
{
	return _value;
}

void string::register_gcables(gc::gc& gc) const noexcept
{
	gc.register_gcable(_value.get());
}

bia::gc::gcable<string> string::_lower() const
{
	const auto gc     = gc::gc::active_gc();
	const auto length = std::char_traits<char>::length(_value.get());
	const auto mem    = static_cast<char*>(gc->allocate(length + 1).release());

	std::transform(_value.get(), _value.get() + length + 1, mem, [](char c) { return std::tolower(c); });

	return gc->template construct<string>(mem);
}

bia::gc::gcable<string> string::_upper() const
{
	const auto gc     = gc::gc::active_gc();
	const auto length = std::char_traits<char>::length(_value.get());
	const auto mem    = static_cast<char*>(gc->allocate(length + 1).release());

	std::transform(_value.get(), _value.get() + length + 1, mem, [](char c) { return std::toupper(c); });

	return gc->template construct<string>(mem);
}
