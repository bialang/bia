#include "list.hpp"

#include "../cast/cast.hpp"
#include "../function/generator.hpp"
#include "../function/method.hpp"
#include "string.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
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

bia::gc::gcable<bia::member::member> list::invoke(parameters_type params, invoke_context& context)
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
		thread::lock::guard<decltype(_mutex)> lock{ _mutex };

		return creator::create(_data.size());
	} else if (!name.compare("capacity")) {
		thread::lock::guard<decltype(_mutex)> lock{ _mutex };

		return creator::create(_data.capacity());
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
		thread::lock::guard<decltype(_mutex)> lock{ _mutex };

		return creator::create(_data.empty());
	} else if (!name.compare("clear")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_clear)>>(
		    *this, &list::_clear);
	} else if (!name.compare("front")) {
		thread::lock::guard<decltype(_mutex)> lock{ _mutex };

		return creator::create(_data.front());
	} else if (!name.compare("back")) {
		thread::lock::guard<decltype(_mutex)> lock{ _mutex };

		return creator::create(_data.back());
	} else if (!name.compare("insert")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_insert)>>(
		    *this, &list::_insert);
	} else if (!name.compare("erase")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_erase)>>(
		    *this, &list::_erase);
	} else if (!name.compare("reverse")) {
		return gc::gc::active_gc()->template construct<function::method<true, decltype(&list::_reverse)>>(
		    *this, &list::_reverse);
	} else if (!name.compare("__iter__")) {
		class iterator : public gc::object::base
		{
		public:
			iterator(list* parent) : _parent{ parent }
			{}
			void gc_mark_children(bool mark) const noexcept override
			{
				gc::object::gc_mark(_parent, mark);
			}
			gc::gcable<member> next()
			{
				thread::lock::guard<decltype(_parent->_mutex)> lock{ _parent->_mutex };

				if (_index >= _parent->_data.size()) {
					return function::stop_iteration;
				}

				return _parent->_data[_index++];
			}

		protected:
			void register_gcables(gc::gc& gc) const noexcept override
			{}

		private:
			list* _parent;
			std::size_t _index = 0;
		};

		return gc::gc::active_gc()
		    ->construct<function::generator<function::method<false, decltype(&iterator::next)>>>(
		        iterator{ this }, &iterator::next);
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
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	for (auto child : _data) {
		gc.register_gcable(child);
	}
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

void list::_clear()
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	_data.clear();
}

void list::_insert(connector::parameters_type params)
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	const auto index = util::min(cast::cast<std::size_t>(*params[0]), _data.size());

	_data.reserve(_data.size() + params.size() - 1);
	_data.insert(_data.begin() + index, params.begin() + 1, params.end());
}

void list::_erase(connector::parameters_type params)
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	const auto index = util::min(cast::cast<std::size_t>(*params[0]), _data.size());
	const auto count =
	    params.size() > 1 ? util::min(cast::cast<std::size_t>(*params[1]), _data.size() - index) : 1;

	_data.erase(_data.begin() + index, _data.begin() + index + count);
}

void list::_reverse()
{
	thread::lock::guard<decltype(_mutex)> lock{ _mutex };

	std::reverse(_data.begin(), _data.end());
}
