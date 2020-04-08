#ifndef BIA_BVM_CONTEXT_HPP_
#define BIA_BVM_CONTEXT_HPP_

#include <gc/gc.hpp>
#include <memory>
#include <util/gsl.hpp>

namespace bia {
namespace bvm {

class context
{
public:
	context(util::not_null<std::shared_ptr<gc::gc>> gc) : _gc(std::move(gc.get()))
	{}
	gc::gc& gc()
	{
		return *_gc;
	}

private:
	std::shared_ptr<gc::gc> _gc;
};

} // namespace bvm
} // namespace bia

#endif