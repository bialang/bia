#include <bvm/bvm.hpp>
#include <bvm/framework/int_member.hpp>
#include <bvm/op_code.hpp>
#include <util/endian.hpp>

namespace bia {
namespace bvm {

inline op_code_type next_op_code(int8_t*& ptr)
{
	auto tmp = util::from_little_endian<op_code_type>(ptr);

	ptr += sizeof(op_code_type);

	return tmp;
}

void bvm::execute(context& context, const code& code)
{
	auto instruction_ptr		   = code.byte_code.first;
	const auto instruction_ptr_end = instruction_ptr + code.byte_code.second - max_instruction_size;
	const auto gc				   = context.gc();

	// register
	auto gc_token = gc->register_thread(code.temp_member_count(), code.local_member_count());

	while (instruction_ptr < instruction_ptr_end) {
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