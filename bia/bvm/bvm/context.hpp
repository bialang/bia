#ifndef BIA_BVM_CONTEXT_HPP_
#define BIA_BVM_CONTEXT_HPP_

#include "module/loader.hpp"

#include <gc/gc.hpp>
#include <gc/object/base.hpp>
#include <member/member.hpp>
#include <member/native/dict.hpp>
#include <memory>
#include <util/gsl.hpp>

namespace bia {
namespace bvm {

class context : private gc::object::base
{
public:
	context(util::not_null<std::shared_ptr<gc::gc>> gc) noexcept
	    : _gc(std::move(gc.get())), _loader(_gc.get())
	{
		_gc->register_root(static_cast<gc::object::base*>(this));
	}
	~context()
	{
		_gc->deregister_root(static_cast<gc::object::base*>(this));
	}
	gc::gc& gc() noexcept
	{
		return *_gc;
	}
	member::native::dict& symbols() noexcept
	{
		return _symbols;
	}
	module::loader& loader() noexcept
	{
		return _loader;
	}

private:
	std::shared_ptr<gc::gc> _gc;
	member::native::dict _symbols;
	module::loader _loader;

	void gc_mark_children(bool mark) const noexcept override
	{
		_symbols.gc_mark_children(mark);
		_loader.gc_mark_children(mark);
	}
	void register_gcables(gc::gc& gc) const noexcept override
	{}
};

} // namespace bvm
} // namespace bia

#endif