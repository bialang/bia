#include "bvm.hpp"

#include "instruction_pointer.hpp"
#include "native_operations.hpp"
#include "resource_operations.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/bytecode/operation.hpp>
#include <bia/error/exception.hpp>
#include <bia/member/function/base.hpp>

using namespace bia;

template<bool Conditional, bool IfTrue = false>
inline void execute_jump(bvm::Operation op, bvm::Instruction_pointer& ip, bool test_register)
{
	std::int64_t offset = 0;
	switch (op.variation) {
	case 0: offset = ip.read<std::int8_t>(); break;
	case 1: offset = ip.read<std::int16_t>(); break;
	case 2: offset = ip.read<std::int32_t>(); break;
	case 3: offset = ip.read<std::int64_t>(); break;
	}
	if (!Conditional || test_register == IfTrue) {
		ip += offset;
	}
}

void bvm::execute(util::Span<const util::Byte*> instructions, memory::Frame frame,
                  const resource::Resources& resources, internal::Context& context)
{
	using namespace bytecode;
	Instruction_pointer ip{ instructions };
	bool test_register = false;

	while (ip) {
		const auto op = ip.fetch_and_decode();
		switch (op.op_code) {
		case Op_code::load: {
			const std::int32_t destination = ip.read<std::int32_t>();
			switch (op.variation) {
			case 0: frame.store(destination, ip.read<std::uint8_t>()); break;
			case 1: frame.store(destination, ip.read<std::uint16_t>()); break;
			case 2: frame.store(destination, ip.read<std::uint32_t>()); break;
			case 3: frame.store(destination, ip.read<std::uint64_t>()); break;
			}
			break;
		}
		case Op_code::copy: native_integral_operation<Select_arg<false>, false>(op, ip, frame); break;
		case Op_code::unsigned_raw_operation: {
			using bytecode::Operation;
			switch (ip.read<Operation>()) {
			case Operation::addition: native_integral_operation<Plus, false>(op, ip, frame); break;
			case Operation::subtraction: native_integral_operation<Minus, false>(op, ip, frame); break;
			case Operation::multiplication: native_integral_operation<Multiplies, false>(op, ip, frame); break;
			case Operation::division: native_integral_operation<Divides, false>(op, ip, frame); break;
			case Operation::equal: test_register = native_integral_test<Equal_to, false>(op, ip, frame); break;
			case Operation::not_equal:
				test_register = native_integral_test<Not_equal_to, false>(op, ip, frame);
				break;
			default: BIA_THROW(error::Code::bad_operation);
			}
			break;
		}
		case Op_code::truthy: {
			const std::int32_t arg = ip.read<std::int32_t>();
			switch (op.variation) {
			case 0: test_register = static_cast<bool>(frame.load<std::uint8_t>(arg)); break;
			case 1: test_register = static_cast<bool>(frame.load<std::uint16_t>(arg)); break;
			case 2: test_register = static_cast<bool>(frame.load<std::uint32_t>(arg)); break;
			case 3: test_register = static_cast<bool>(frame.load<std::uint64_t>(arg)); break;
			}
			break;
		}
		case Op_code::jump: execute_jump<false>(op, ip, test_register); break;
		case Op_code::jump_if_false: execute_jump<true, false>(op, ip, test_register); break;
		case Op_code::jump_if_true: execute_jump<true, true>(op, ip, test_register); break;
		case Op_code::booleanize: frame.store(ip.read<std::int32_t>(), static_cast<bool>(test_register)); break;
		case Op_code::load_resource: {
			const std::int32_t arg    = ip.read<std::int32_t>();
			const std::uint32_t index = ip.read<std::uint32_t>();
			const auto& resource      = resources.at(index);
			if (resource.is_type<memory::gc::GC_able<memory::gc::String*>>()) {
				frame.store(arg, resource.get<memory::gc::GC_able<memory::gc::String*>>(), true);
			} else if (resource.is_type<memory::gc::GC_able<memory::gc::Regex*>>()) {
				frame.store(arg, resource.get<memory::gc::GC_able<memory::gc::Regex*>>(), true);
			} else {
				// TODO
				BIA_ASSERT(false);
			}
			break;
		}
		case Op_code::resource_operation: {
			using bytecode::Operation;
			const auto operation = ip.read<Operation>();
			switch (operation) {
			case Operation::equal: test_register = resource_operation_test<Equal_to>(op, ip, frame); break;
			case Operation::not_equal: test_register = resource_operation_test<Not_equal_to>(op, ip, frame); break;
			case Operation::in: test_register = resource_operation_test<Inside_of>(op, ip, frame); break;
			default: BIA_THROW(error::Code::bad_operation);
			}
			break;
		}
		case Op_code::load_from_context: {
			const std::int32_t arg    = ip.read<std::int32_t>();
			const std::uint32_t index = ip.read<std::uint32_t>();
			const auto& resource      = resources.at(index);
			BIA_ASSERT(resource.is_type<memory::gc::GC_able<memory::gc::String*>>());
			frame.store(
			  arg, context.import(resource.get<memory::gc::GC_able<memory::gc::String*>>()->string.c_str()), true);
			break;
		}
		case Op_code::invoke: {
			const std::int32_t arg = ip.read<std::int32_t>();
			frame.load<memory::gc::GC_able<member::function::Base*>>(arg)->invoke(
			  { frame, static_cast<std::size_t>(arg) });
			break;
		}
		default: BIA_THROW(error::Code::bad_opcode);
		}
	}
}
