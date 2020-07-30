#ifndef BIA_BSL_SYS_HPP_
#define BIA_BSL_SYS_HPP_

#include <bia/bvm/module/module.hpp>
#include <bia/gc/gc.hpp>
#include <bia/gc/object/pointer.hpp>
#include <bia/member/native/dict.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace bsl {

class sys : public bvm::module::module
{
public:
	sys(gc::gc& gc, util::span<const char* const*> arguments);
	version_type version() const noexcept override;
	util::not_null<member::member*> create(gc::gc& gc) override;
	void gc_mark_children(bool mark) const noexcept override;

protected:
	void register_gcables(gc::gc& gc) const noexcept override;

private:
	gc::object::immutable_pointer<member::native::dict> _symbols;

	static member::native::dict* _init(gc::gc& gc, util::span<const char* const*> arguments);
};

} // namespace bsl
} // namespace bia

#endif
