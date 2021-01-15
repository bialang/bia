#include "bvm.hpp"

#include "instruction_pointer.hpp"

#include <bia/bytecode/op_code.hpp>

using namespace bia;

void bvm::execute(context& context, util::span<const util::byte_type*> instructions, gc::root& resources)
{
	auto token = context.gc().register_thread(1024);
	auto stack = token->stack_view();
	return execute(context, instructions, resources, stack, *token);
}

void bvm::execute(context& context, util::span<const util::byte_type*> instructions, gc::root& resources,
                  gc::Stack<std::int32_t>& stack, gc::token& token)
{
	using namespace bytecode;
	instruction_pointer ip(instructions);
	auto& gc = context.gc();

	while (ip) {
		const auto op_code = ip.next_op_code();
		switch (to_op_code_base(op_code)) {
		case oc_push: {
			stack.push(ip.read<std::int32_t>());
			break;
		}
		case oc_pop: {
			stack.pop(ip.read<std::uint8_t>());
			break;
		}
		default: BIA_THROW(bia::error::Code::bad_opcode);
		}
	}

	return {};
}
