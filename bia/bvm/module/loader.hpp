#ifndef BIA_BVM_MODULE_LOADER_HPP_
#define BIA_BVM_MODULE_LOADER_HPP_

#include "module.hpp"

#include <bia/gc/gc.hpp>
#include <bia/gc/object/base.hpp>
#include <bia/gc/object/pointer.hpp>
#include <map>
#include <bia/member/native/string.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace bvm {
namespace module {

class loader : public gc::object::base
{
public:
	loader(util::not_null<gc::gc*> gc) noexcept;
	util::not_null<util::gcable<member::member*>>
	    load(util::not_null<util::gcable<member::native::string*>> name);
	void add_module(util::not_null<util::gcable<member::native::string*>> name,
	                util::not_null<util::gcable<module*>> module);
	void gc_mark_children(bool mark) const noexcept override;

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{}

private:
	struct compare
	{
		typedef gc::object::immutable_pointer<member::native::string> arg_type;

		bool operator()(arg_type left, arg_type right) const noexcept
		{
			return left->compare(*right);
		}
	};

	gc::gc* _gc;
	std::map<gc::object::immutable_pointer<member::native::string>, gc::object::immutable_pointer<module>,
	         compare>
	    _modules;
};

} // namespace module
} // namespace bvm
} // namespace bia

#endif
