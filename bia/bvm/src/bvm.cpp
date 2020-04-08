#include "bvm/bvm.hpp"

#include "bvm/instruction_pointer.hpp"

#include <bytecode/op_code.hpp>
#include <member/member.hpp>


using namespace bia::bvm;
using namespace bia::bytecode;

void bvm::execute(const bia::util::byte* first, const bia::util::byte* last)
{
	instruction_pointer ip{ first, last };
	member::member::test_type test_register{ 0 };

	while (ip) {
		const auto op_code = ip.next_op_code();

		switch (op_code) {
		case oc_return_void: return;
		case oc_jump: ip += ip.read<std::int32_t>(); break;
		case oc_jump_true: {
			if (test_register) {
				ip += ip.read<std::int32_t>();
			}

			break;
		}
		case oc_jump_false: {
			if (!test_register) {
				ip += ip.read<std::int32_t>();
			}

			break;
		}
		case oc_instantiate: {
		}
		default: throw;
		}
	}
}
