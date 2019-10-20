#include <bvm/bvm.hpp>
#include <bvm/instruction_pointer.hpp>
#include <bytecode/op_code.hpp>
#include <exception/invalid_op_code_exception.hpp>
#include <member/member.hpp>
#include <util/objects.hpp>

namespace bia {
namespace bvm {

using namespace bytecode;
template<typename T>
using rnn = util::objects::require_non_null<T>;

void bvm::execute(context& context, const compiler::code& code)
{
	instruction_pointer instruction_ptr(code.begin(), code.end());
	auto& gc			   = context.gc();
	auto& stack			   = context.stack();
	const auto stack_frame = stack.create_frame();
	auto test_register	 = false;

	// register and allocate members
	auto gc_token = gc.register_thread(code.temp_member_count() + 1 /* plus 1 because of the accumulator */,
										code.local_member_count());

	while (instruction_ptr) {
		/* auto-generated switch for evaluating byte code instructions */
		switch (instruction_ptr.next_op_code()) {
		/** P-Type */
		case OC_RETURN_VOID: {
			return;
		}
		/** int-Type */
		case (OC_JUMP - IIOCO_INT32): {
			auto x0 = instruction_ptr.read<std::int32_t>();
			instruction_ptr += x0;
			break;
		}
		case (OC_JUMP - IIOCO_INT8): {
			auto x0 = instruction_ptr.read<std::int8_t>();
			instruction_ptr += x0;
			break;
		}
		case (OC_JUMP_TRUE - IIOCO_INT32): {
			auto x0 = instruction_ptr.read<std::int32_t>();
			instruction_ptr += test_register ? x0 : 0;
			break;
		}
		case (OC_JUMP_TRUE - IIOCO_INT8): {
			auto x0 = instruction_ptr.read<std::int8_t>();
			instruction_ptr += test_register ? x0 : 0;
			break;
		}
		case (OC_JUMP_FALSE - IIOCO_INT32): {
			auto x0 = instruction_ptr.read<std::int32_t>();
			instruction_ptr += test_register ? 0 : x0;
			break;
		}
		case (OC_JUMP_FALSE - IIOCO_INT8): {
			auto x0 = instruction_ptr.read<std::int8_t>();
			instruction_ptr += test_register ? 0 : x0;
			break;
		}
		case (OC_POP - IIOCO_INT32): {
			auto x0 = instruction_ptr.read<std::int32_t>();
			stack.pop(x0);
			break;
		}
		case (OC_POP - IIOCO_INT8): {
			auto x0 = instruction_ptr.read<std::int8_t>();
			stack.pop(x0);
			break;
		}
		/** I-Type */
		case (OC_PUSH_IMMEDIATE - IOCO_STRING): {
			auto x0 = "some placeholder";
			stack.push(x0);
			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_TEST_REGISTER): {
			auto x0 = test_register;
			stack.push(x0);
			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_FLOAT): {
			auto x0 = instruction_ptr.read</*placeholder*/ std::int64_t>();
			stack.push(x0);
			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_INT64): {
			auto x0 = instruction_ptr.read<std::int64_t>();
			stack.push(x0);
			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_INT32): {
			auto x0 = instruction_ptr.read<std::int32_t>();
			stack.push(x0);
			break;
		}
		case (OC_PUSH_IMMEDIATE - IOCO_INT8): {
			auto x0 = instruction_ptr.read<std::int8_t>();
			stack.push(x0);
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
			auto x0 = instruction_ptr.read</*placeholder*/ std::int64_t>();

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_INT64): {
			auto x0 = instruction_ptr.read<std::int64_t>();

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_INT32): {
			auto x0 = instruction_ptr.read<std::int32_t>();

			break;
		}
		case (OC_RETURN_IMMEDIATE - IOCO_INT8): {
			auto x0 = instruction_ptr.read<std::int8_t>();

			break;
		}
		/** M-Type */
		case (OC_PUSH_MEMBER - MOCO_TEMP): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];

			break;
		}
		case (OC_PUSH_MEMBER - MOCO_TINY_TEMP): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];

			break;
		}
		case (OC_RETURN_MEMBER - MOCO_TEMP): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];

			break;
		}
		case (OC_RETURN_MEMBER - MOCO_TINY_TEMP): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];

			break;
		}
		case (OC_TEST - MOCO_TEMP): {
			auto& x0	  = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			test_register = static_cast<bool>(x0.get<member::member>()->test());
			break;
		}
		case (OC_TEST - MOCO_TINY_TEMP): {
			auto& x0	  = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			test_register = static_cast<bool>(x0.get<member::member>()->test());
			break;
		}
		/** MMintint-Type */
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT + IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT + IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT + IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT + IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT + IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT + IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT + IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT + IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT + IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT + IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT + IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL -
			  (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT + IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL - (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT +
						 IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL - (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT32) * IIOCO_COUNT +
						 IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int32_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL - (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT +
						 IIOCO_INT32)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int32_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		case (OC_CALL - (((MOCO_TINY_TEMP * MOCO_COUNT + MOCO_TINY_TEMP) * IIOCO_COUNT + IIOCO_INT8) * IIOCO_COUNT +
						 IIOCO_INT8)): {
			auto& x0 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto& x1 = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];
			auto x2  = instruction_ptr.read<std::int8_t>();
			auto x3  = instruction_ptr.read<std::int8_t>();
			gc_token.set(x0, x1.get<member::member>()->call(&stack, x2));
			stack.pop(x3);
			break;
		}
		default: BIA_THROW(exception::invalid_op_code_exception, u"invalid op code");
		}
		/* auto-generated switch for evaluating byte code instructions */
	}
}

} // namespace bvm
} // namespace bia
