#include <bvm.hpp>
#include <bvm/framework/int_member.hpp>
#include <bvm/op_code.hpp>

namespace bia {
namespace bvm {

inline void set(bool gc_active, gc::object_ptr& dest, gc::object_ptr&& src)
{
	if (gc_active) {
	}

	dest = src;
}

inline op_code_type next_op_code(int8_t*& ptr)
{}

void bvm::execute(context& context, const code& code)
{
	auto instruction_ptr		   = code.byte_code.first;
	const auto instruction_ptr_end = instruction_ptr + code.byte_code.second - max_instruction_size;
	const auto gc				   = context.gc();

	// register
	auto gc_token = gc->register_thread();

	// allocate roots
	auto temp_members  = gc->create_root(code.temp_member_count());
	auto local_members = gc->create_root(code.local_member_count());

	while (instruction_ptr < instruction_ptr_end) {
		// update status
		gc_token.update();

		// read next instruction
		auto op_code = next_op_code(instruction_ptr);

		/* auto-generated switch for evaluating byte code instructions */
		switch (op_code) {}
		/* auto-generated switch for evaluating byte code instructions */
	}

gt_return:;
}

} // namespace bvm
} // namespace bia