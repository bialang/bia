#include <bvm/bvm.hpp>
#include <bvm/instruction_pointer.hpp>
#include <member/member.hpp>
#include <exception/invalid_op_code_exception.hpp>

namespace bia {
namespace bvm {

void bvm::execute(context& context, const compiler::code& code)
{
	instruction_pointer instruction_ptr(code.begin(), code.end());
	const auto gc = context.gc();
	member::member::bool_type test_register = 0;

	// register and allocate members
	auto gc_token = gc->register_thread(code.temp_member_count(), code.local_member_count());

	while (instruction_ptr) {
		/* auto-generated switch for evaluating byte code instructions */
		switch (instruction_ptr.next_op_code()) {
		/** P-Type */
		case OC_RETURN_VOID: {
			goto gt_return;
			break;
		}
		/** int-Type */
		case (OC_JUMP - IIOCO_INT32): {
			auto x0 = instruction_ptr.read<int32_t>();
			instruction_ptr += x0;
			break;
		}
		case (OC_JUMP - IIOCO_INT8): {
			auto x0 = instruction_ptr.read<int8_t>();
			instruction_ptr += x0;
			break;
		}
		case (OC_JUMP_TRUE - IIOCO_INT32): {
			auto x0 = instruction_ptr.read<int32_t>();
			instruction_ptr += test_register ? x0 : 0;
			break;
		}
		case (OC_JUMP_TRUE - IIOCO_INT8): {
			auto x0 = instruction_ptr.read<int8_t>();
			instruction_ptr += test_register ? x0 : 0;
			break;
		}
		case (OC_JUMP_FALSE - IIOCO_INT32): {
			auto x0 = instruction_ptr.read<int32_t>();
			instruction_ptr += test_register ? 0 : x0;
			break;
		}
		case (OC_JUMP_FALSE - IIOCO_INT8): {
			auto x0 = instruction_ptr.read<int8_t>();
			instruction_ptr += test_register ? 0 : x0;
			break;
		}
		/** I-Type */
		case (OC_PUSH_IMMEDIATE - IOCO_STRING): {
			auto x0 = "some placeholder";

			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_TEST_REGISTER): {
			auto x0 = test_register;

			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_FLOAT): {
			auto x0 = instruction_ptr.read<double>();

			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_INT64): {
			auto x0 = instruction_ptr.read<int64_t>();

			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_INT32): {
			auto x0 = instruction_ptr.read<int32_t>();

			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_INT8): {
			auto x0 = instruction_ptr.read<int8_t>();

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_STRING): {
			auto x0 = "some placeholder";

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_TEST_REGISTER): {
			auto x0 = test_register;

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_FLOAT): {
			auto x0 = instruction_ptr.read<double>();

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_INT64): {
			auto x0 = instruction_ptr.read<int64_t>();

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_INT32): {
			auto x0 = instruction_ptr.read<int32_t>();

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_INT8): {
			auto x0 = instruction_ptr.read<int8_t>();

			break;
		}
		/** M-Type */
		default: BIA_THROW(exception::invalid_op_code_exception, u"invalid op code");
		}
		/* auto-generated switch for evaluating byte code instructions */
	}

gt_return:;
}

} // namespace bvm
} // namespace bia