#ifndef BIA_BVM_CONTEXT_HPP_
#define BIA_BVM_CONTEXT_HPP_

#include <gc/gc.hpp>
#include <member/member.hpp>
#include <member/native/dict.hpp>
#include <memory>
#include <util/gsl.hpp>

namespace bia {
namespace bvm {

class context
{
public:
	context(util::not_null<std::shared_ptr<gc::gc>> gc) noexcept : _gc(std::move(gc.get()))
	{
		_gc->register_root(&_symbols);
	}
	~context()
	{
		_gc->deregister_root(&_symbols);
	}
	gc::gc& gc() noexcept
	{
		return *_gc;
	}
	member::native::dict& symbols() noexcept
	{
		return _symbols;
	}

private:
	std::shared_ptr<gc::gc> _gc;
	member::native::dict _symbols;
};

} // namespace bvm
} // namespace bia

#endif