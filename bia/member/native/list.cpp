#include "list.hpp"

#include "../function/method.hpp"
#include "string.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/thread/lock/guard.hpp>

using namespace bia::member::native;

list::list(std::vector<member*> data) noexcept : _data{ std::move(data) }
{}

list::flag_type list::flags() const
{
	return flag_none;
}

list::test_type list::test(test_operator op, const member& right) const
{
	if (op == test_operator::self) {
		return !_data.empty();
	}

	return {};
}

bia::gc::gcable<bia::member::member> list::copy() const
{
	return {};
	// return gc::gc::active_gc()->template construct<list>(*this);
}

bia::gc::gcable<bia::member::member> list::invoke(parameters_type params)
{
	return {};
}

bia::gc::gcable<bia::member::member> list::operation(const member& right, infix_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> list::self_operation(self_operator op)
{
	return {};
}

bia::gc::gcable<bia::member::member> list::get(const native::string& name)
{
	if (!name.compare("size")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_size)>>(
		    *this, &list::_size);
	} else if (!name.compare("capacity")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_size)>>(
		    *this, &list::_size);
	} else if (!name.compare("push")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_push)>>(
		    *this, &list::_push);
	}

	return {};
}

list::float_type list::as_float() const noexcept
{
	return {};
}

list::int_type list::as_int() const noexcept
{
	return {};
}

bool list::as_data(const std::type_info& type, void* output)
{
	return const_cast<const list*>(this)->as_data(type, output);
}

bool list::as_data(const std::type_info& type, void* output) const
{
	if (type == typeid(std::vector<member*>)) {
		*static_cast<std::vector<member*>*>(output) = _data;

		return true;
	}

	return false;
}

void list::gc_mark_children(bool mark) const noexcept
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	for (auto child : _data) {
		if (child) {
			gc::object::gc_mark(child, mark);
		}
	}
}

void list::register_gcables(gc::gc& gc) const noexcept
{}

std::size_t list::_size() const
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	return _data.size();
}

std::size_t list::_capacity() const
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	return _data.capacity();
}

void list::_push(connector::parameters_type params)
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	_data.reserve(_data.size() + params.size());

	for (auto i : params) {
		_data.push_back(i);
	}
}
