#include <bvm/bvm.hpp>
#include <bvm/instruction_pointer.hpp>

namespace bia {
namespace bvm {

void bvm::execute(context& context, const compiler::code& code)
{
	instruction_pointer instruction_ptr(code.begin(), code.end());
	const auto gc = context.gc();

	// register and allocate members
	auto gc_token = gc->register_thread(code.temp_member_count(), code.local_member_count());

	while (instruction_ptr) {
		/* auto-generated switch for evaluating byte code instructions */
		switch (instruction_ptr.next_op_code()) {}
		/* auto-generated switch for evaluating byte code instructions */
	}

gt_return:;
}

} // namespace bvm
} // namespace bia