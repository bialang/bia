#include "bvm.hpp"

#include "instruction_pointer.hpp"
#include "native_operations.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/bytecode/operation.hpp>
#include <bia/error/exception.hpp>

using namespace bia;

struct String
{
	const char* ptr;
	std::uint32_t length;
};

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
	bool test_register = false;

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
		case Op_code::unsigned_raw_operation: {
			using bytecode::Operation;
			switch (ip.read<Operation>()) {
			case Operation::addition: native_integral_operation<Plus, false>(op, ip, stack); break;
			case Operation::subtraction: native_integral_operation<Minus, false>(op, ip, stack); break;
			case Operation::multiplication: native_integral_operation<Multiplies, false>(op, ip, stack); break;
			case Operation::division: native_integral_operation<Divides, false>(op, ip, stack); break;
			case Operation::equal: test_register = native_integral_test<Equal_to, false>(op, ip, stack); break;
			case Operation::not_equal:
				test_register = native_integral_test<Not_equal_to, false>(op, ip, stack);
				break;
			default: BIA_THROW(error::Code::bad_operation);
			}
			break;
		}
		case Op_code::truthy: {
			const std::int32_t arg = ip.read<std::int32_t>();
			switch (op.size) {
			case 0: test_register = static_cast<bool>(stack.load<std::uint8_t>(arg)); break;
			case 1: test_register = static_cast<bool>(stack.load<std::uint16_t>(arg)); break;
			case 2: test_register = static_cast<bool>(stack.load<std::uint32_t>(arg)); break;
			case 3: test_register = static_cast<bool>(stack.load<std::uint64_t>(arg)); break;
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
				static_assert(offsetof(String, ptr) == 0, "bad pointer offset");
				const auto& str = resource.get<util::Span<const char*>>();
				stack.store(arg, String{ str.data(), static_cast<std::uint32_t>(str.size()) }, true);
			} else {
				// TODO
				BIA_ASSERT(false);
			}
			break;
		}
		case Op_code::resource_operation: {
			using bytecode::Operation;
			const auto operation    = ip.read<Operation>();
			const std::int32_t arg0 = ip.read<std::int32_t>();
			const std::int32_t arg1 = ip.read<std::int32_t>();
			const auto left         = stack.load<String>(arg0);
			const auto right        = stack.load<String>(arg1);
			switch (operation) {
			case Operation::equal:
				test_register = left.length == right.length && !std::strcmp(left.ptr, right.ptr);
				break;
			case Operation::not_equal:
				test_register = left.length != right.length || std::strcmp(left.ptr, right.ptr);
				break;
			case Operation::in: test_register = std::strstr(right.ptr, left.ptr) != nullptr; break;
			default: BIA_THROW(error::Code::bad_operation);
			}
			break;
		}
		default: BIA_THROW(error::Code::bad_opcode);
		}
	}
}
