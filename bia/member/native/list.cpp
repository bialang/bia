#include "list.hpp"

#include "../cast/cast.hpp"
#include "../function/method.hpp"
#include "string.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/thread/lock/guard.hpp>
#include <bia/util/aggregate.hpp>

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
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_capacity)>>(
		    *this, &list::_capacity);
	} else if (!name.compare("push")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_push)>>(
		    *this, &list::_push);
	} else if (!name.compare("pop")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_pop)>>(
		    *this, &list::_pop);
	} else if (!name.compare("reserve")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_reserve)>>(
		    *this, &list::_reserve);
	} else if (!name.compare("shrink_to_fit")) {
		return gc::gc::active_gc()
		    ->template construct<function::method<true, decltype(&list::_shrink_to_fit)>>(
		        *this, &list::_shrink_to_fit);
	} else if (!name.compare("empty")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_empty)>>(
		    *this, &list::_empty);
	} else if (!name.compare("clear")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_clear)>>(
		    *this, &list::_clear);
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

void list::_pop(connector::parameters_type params)
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	const auto count = params.size() == 1 ? util::min(cast::cast<std::size_t>(*params[0]), _data.size()) : 1;

	_data.erase(_data.end() - count, _data.end());
}

void list::_reserve(std::size_t size)
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	_data.reserve(size);
}

void list::_shrink_to_fit()
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	_data.shrink_to_fit();
}

bool list::_empty()
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	return _data.empty();
}

void list::_clear()
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	_data.clear();
}
