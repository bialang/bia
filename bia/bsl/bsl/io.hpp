#ifndef BIA_BSL_IO_HPP_
#define BIA_BSL_IO_HPP_

#include <bvm/module/module.hpp>
#include <gc/object/pointer.hpp>
#include <member/native/dict.hpp>

namespace bia {
namespace bsl {

class io : public bvm::module::module
{
public:
	io(gc::gc& gc);
	version_type version() const noexcept override;
	util::not_null<member::member*> create(gc::gc& gc) override;
	void gc_mark_children(bool mark) const noexcept override;

protected:
	void register_gcables(gc::gc& gc) const noexcept override;

private:
	gc::object::immutable_pointer<member::native::dict> _symbols;

	static member::native::dict* _init(gc::gc& gc);
};

} // namespace bsl
} // namespace bia

#endif