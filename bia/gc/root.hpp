#ifndef BIA_GC_ROOT_HPP_
#define BIA_GC_ROOT_HPP_

#include "gc.hpp"
#include "gcable.hpp"
#include "object/base.hpp"
#include "object/pointer.hpp"

#include <bia/util/gsl.hpp>

namespace bia {
namespace member {

class member;

} // namespace member
namespace gc {

class root : public object::base
{
public:
	class builder;

	typedef object::immutable_pointer<member::member> element_type;

	~root()
	{
		_gc->deregister_root(this);

		for (auto& i : _data) {
			i.~immutable_pointer();
		}

		_gc->allocator()->deallocate(_data.data());
	}
	const element_type& at(std::size_t index) const
	{
		return _data.at(index);
	}
	const element_type* begin() const
	{
		return _data.begin();
	}
	const element_type* end() const
	{
		return _data.end();
	}

protected:
	void gc_mark_children(bool mark) const noexcept override
	{
		for (auto& i : _data) {
			object::gc_mark(i.get(), mark);
		}
	}
	void register_gcables(gc& gc) const noexcept override
	{}

private:
	gc* _gc;
	util::Span<element_type*> _data;

	root(gc* gc, util::owner<util::Span<element_type*>> data) : _data{ std::move(data) }
	{
		_gc = gc;

		_gc->register_root(this);
	}
};

class root::builder
{
public:
	builder(gc* gc, std::size_t size)
	{
		if ((_gc = gc)) {
			_cursor = static_cast<element_type*>(
			    _gc->allocator()->checked_allocate(size * sizeof(element_type)).get());
			_data = { _cursor, size };
		}
	}
	builder(builder&& move) noexcept
	{
		std::swap(_gc, move._gc);
		std::swap(_cursor, move._cursor);
		std::swap(_data, move._data);
	}
	~builder()
	{
		_discard();
	}
	void add(member::member* ptr)
	{
		BIA_EXPECTS(_cursor != _data.end());

		new (_cursor++) element_type{ ptr };
	}
	std::unique_ptr<root> finish()
	{
		BIA_EXPECTS(finishable());

		std::unique_ptr<root> r{ new root{ _gc, _data } };

		_gc     = nullptr;
		_cursor = nullptr;
		_data   = {};

		return r;
	}
	bool finishable() const noexcept
	{
		return _gc && _cursor == _data.end();
	}
	builder& operator=(builder&& move)
	{
		_discard();

		_gc          = move._gc;
		_cursor      = move._cursor;
		_data        = move._data;
		move._gc     = nullptr;
		move._cursor = nullptr;
		move._data   = {};

		return *this;
	}

private:
	gc* _gc               = nullptr;
	element_type* _cursor = nullptr;
	util::Span<element_type*> _data;

	void _discard()
	{
		if (_gc) {
			_gc->allocator()->deallocate(_data.data());
		}
	}
};

} // namespace gc
} // namespace bia

#endif
