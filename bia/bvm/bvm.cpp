#include "bvm.hpp"

#include "instruction_pointer.hpp"
#include "native_operations.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/bytecode/operation.hpp>
#include <bia/error/exception.hpp>

using namespace bia;

template<bool Conditional, bool IfTrue = false>
inline void execute_jump(bvm::Operation op, bvm::Instruction_pointer& ip, bool test_register)
{
	std::int64_t offset = 0;
	switch (op.size) {
	case 0: offset = ip.read<std::int8_t>(); break;
	case 1: offset = ip.read<std::int16_t>(); break;
	case 2: offset = ip.read<std::int32_t>(); break;
	case 3: offset = ip.read<std::int64_t>(); break;
	}
	if (!Conditional || test_register == IfTrue) {
		ip += offset;
	}
}

void bvm::execute(util::Span<const util::Byte*> instructions, memory::Stack& stack,
                  const resource::Resources& resources)
{
	using namespace bytecode;
	Instruction_pointer ip{ instructions };
	int test_register = 0;

	while (ip) {
		const auto op = ip.fetch_and_decode();
		switch (op.op_code) {
		case Op_code::load: {
			const std::int32_t destination = ip.read<std::int32_t>();
			switch (op.size) {
			case 0: stack.store(destination, ip.read<std::uint8_t>()); break;
			case 1: stack.store(destination, ip.read<std::uint16_t>()); break;
			case 2: stack.store(destination, ip.read<std::uint32_t>()); break;
			case 3: stack.store(destination, ip.read<std::uint64_t>()); break;
			}
			break;
		}
		case Op_code::copy: native_integral_operation<Select_arg<false>, false>(op, ip, stack); break;
		case Op_code::unsigned_integral_operation: {
			using bytecode::Infix_operation;
			switch (ip.read<Infix_operation>()) {
			case Infix_operation::addition: native_integral_operation<Plus, false>(op, ip, stack); break;
			case Infix_operation::subtraction: native_integral_operation<Minus, false>(op, ip, stack); break;
			case Infix_operation::multiplication:
				native_integral_operation<Multiplies, false>(op, ip, stack);
				break;
			case Infix_operation::division: native_integral_operation<Divides, false>(op, ip, stack); break;
			default: BIA_THROW(error::Code::bad_infix_operation);
			}
			break;
		}
		case Op_code::unsigned_integral_test: {
			using bytecode::Test_operation;
			switch (ip.read<Test_operation>()) {
			case Test_operation::equal: test_register = native_integral_test<Equal_to, false>(op, ip, stack); break;
			case Test_operation::not_equal:
				test_register = native_integral_test<Not_equal_to, false>(op, ip, stack);
				break;
			default: BIA_THROW(error::Code::bad_test_operation);
			}
			break;
		}
		case Op_code::truthy: {
			const std::int32_t arg = ip.read<std::int32_t>();
			switch (op.size) {
			case 0: test_register = stack.load<std::uint8_t>(arg) ? 1 : 0; break;
			case 1: test_register = stack.load<std::uint16_t>(arg) ? 1 : 0; break;
			case 2: test_register = stack.load<std::uint32_t>(arg) ? 1 : 0; break;
			case 3: test_register = stack.load<std::uint64_t>(arg) ? 1 : 0; break;
			}
			break;
		}
		case Op_code::jump: execute_jump<false>(op, ip, test_register); break;
		case Op_code::jump_if_false: execute_jump<true, false>(op, ip, test_register); break;
		case Op_code::jump_if_true: execute_jump<true, true>(op, ip, test_register); break;
		case Op_code::booleanize: stack.store(ip.read<std::int32_t>(), static_cast<bool>(test_register)); break;
		case Op_code::load_resource: {
			const std::int32_t arg    = ip.read<std::int32_t>();
			const std::uint32_t index = ip.read<std::uint32_t>();
			const auto& resource      = resources.at(index);
			if (resource.is_type<util::Span<const char*>>()) {
				struct String
				{

					const char* ptr;
					std::uint32_t length;
				};
				const auto& str = resource.get<util::Span<const char*>>();
				stack.store(arg, String{ str.data(), static_cast<std::uint32_t>(str.size()) });
			} else {
				// TODO
				BIA_ASSERT(false);
			}
			break;
		}
		default: BIA_THROW(error::Code::bad_opcode);
		}
	}
}
