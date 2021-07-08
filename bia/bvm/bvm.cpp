#include "bvm.hpp"

#include "instruction_pointer.hpp"
#include "native_operations.hpp"
#include "resource_operations.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/bytecode/operation.hpp>
#include <bia/error/exception.hpp>
#include <bia/member/function/base.hpp>
#include <vector>

using namespace bia;

template<typename Type>
inline Type read(util::Span<const util::Byte*> buffer, std::size_t offset)
{
	static_assert(std::is_trivial<Type>::value, "must be Trivial");
	return *reinterpret_cast<const Type*>(buffer.data() + offset);
}

void bvm::execute(util::Span<const util::Byte*> instructions, memory::Frame<true> frame,
                  const resource::Resources& resources, internal::Context& context)
{
	using namespace bytecode;
	Instruction_pointer ip{ instructions };
	bool test_register = false;
	std::vector<util::Span<const util::Byte*>> namespaces;
	namespaces.push_back(context.global_namespace().globals());

	while (ip) {
		const auto op = ip.fetch_and_decode();
		switch (op.op_code) {
		case Op_code::store: {
			const auto destination = ip.read<Address>();
			switch (op.size) {
			case Size::bit_8: frame.store(destination, ip.read<std::uint8_t>()); break;
			case Size::bit_16: frame.store(destination, ip.read<std::uint16_t>()); break;
			case Size::bit_32: frame.store(destination, ip.read<std::uint32_t>()); break;
			case Size::bit_64: frame.store(destination, ip.read<std::uint64_t>()); break;
			}
			break;
		}
		case Op_code::load_resource: {
			const auto destination = ip.read<Address>();
			const auto index       = ip.read<std::uint32_t>();
			const auto& resource   = resources.at(index);
			if (resource.is_type<memory::gc::GC_able<memory::gc::String*>>()) {
				frame.store(destination, resource.get<memory::gc::GC_able<memory::gc::String*>>(), true);
			} else if (resource.is_type<memory::gc::GC_able<memory::gc::Regex*>>()) {
				frame.store(destination, resource.get<memory::gc::GC_able<memory::gc::Regex*>>(), true);
			} else {
				// TODO
				BIA_ASSERT(false);
			}
			break;
		}
		case Op_code::load_from_namespace: {
			const auto destination = ip.read<Address>();
			const auto source      = ip.read<Address>();
			// switch (op.size) {
			// case Size::bit_8:
			// case Size::bit_16:
			// case Size::bit_32:
			// case Size::bit_64:
			// }
			break;
		}
		case Op_code::copy: {
			const auto destination = ip.read<Address>();
			const auto source      = ip.read<Address>();
			switch (op.size) {
			case Size::bit_8: frame.store(destination, frame.load<std::uint8_t>(source)); break;
			case Size::bit_16: frame.store(destination, frame.load<std::uint16_t>(source)); break;
			case Size::bit_32: frame.store(destination, frame.load<std::uint32_t>(source)); break;
			case Size::bit_64: frame.store(destination, frame.load<std::uint64_t>(source)); break;
			}
			break;
		}
		case Op_code::add: native_integral_operation<Addition, false>(op, ip, frame); break;
		case Op_code::fadd: native_floating_operation<Addition>(op, ip, frame); break;
		case Op_code::sub: native_integral_operation<Subtraction, false>(op, ip, frame); break;
		case Op_code::fsub: native_floating_operation<Subtraction>(op, ip, frame); break;
		case Op_code::mul: native_integral_operation<Multiplication, false>(op, ip, frame); break;
		case Op_code::fmul: native_floating_operation<Multiplication>(op, ip, frame); break;
		case Op_code::sdiv: native_integral_operation<Division, true>(op, ip, frame); break;
		case Op_code::udiv: native_integral_operation<Division, false>(op, ip, frame); break;
		case Op_code::fdiv: native_floating_operation<Division>(op, ip, frame); break;
		case Op_code::srem: native_integral_operation<Remainder, true>(op, ip, frame); break;
		case Op_code::urem: native_integral_operation<Remainder, false>(op, ip, frame); break;
		case Op_code::frem: native_floating_operation<Remainder>(op, ip, frame); break;
		case Op_code::bitwise_and: native_integral_operation<Bitwise_and, false>(op, ip, frame); break;
		case Op_code::bitwise_or: native_integral_operation<Bitwise_or, false>(op, ip, frame); break;
		case Op_code::bitwise_xor: native_integral_operation<Bitwise_xor, false>(op, ip, frame); break;
		case Op_code::equal: test_register = native_integral_test<Equality, false>(op, ip, frame); break;
		case Op_code::not_equal: test_register = !native_integral_test<Equality, false>(op, ip, frame); break;
		case Op_code::invoke: {
			const auto function_address = ip.read<Address>();
			const auto function_object = frame.load<memory::gc::GC_able<member::function::Base*>>(function_address);
			function_object->invoke(memory::Frame<true>{ frame, 0 });
			break;
		}
		case Op_code::jump: {
			const auto offset = ip.read<std::int32_t>();
			ip += offset;
			break;
		}
		case Op_code::jump_true: {
			const auto offset = ip.read<std::int32_t>();
			if (test_register) {
				ip += offset;
			}
			break;
		}
		case Op_code::jump_false: {
			const auto offset = ip.read<std::int32_t>();
			if (!test_register) {
				ip += offset;
			}
			break;
		}
		default: BIA_THROW(error::Code::bad_opcode);
		}
	}
}
