#include "disassembler.hpp"

#include "op_code.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/portable/stream.hpp>
#include <cstdint>
#include <iomanip>
#include <type_traits>

enum class A : bia::bytecode::Address
{
};

inline std::ostream& operator<<(std::ostream& out, A a)
{
	out << "%" << std::hex << static_cast<bia::bytecode::Address>(a);
	return out;
}

using namespace bia;

inline std::ostream& out(std::ostream& output, bytecode::Size size, const char* name)
{
	const char* str = "<err>";
	switch (size) {
	case bytecode::Size::bit_8: str = "<8>"; break;
	case bytecode::Size::bit_16: str = "<16>"; break;
	case bytecode::Size::bit_32: str = "<32>"; break;
	case bytecode::Size::bit_64: str = "<64>"; break;
	}
	output << str << " " << std::left << std::setw(14) << name;
	return output;
}

inline std::ostream& out(std::ostream& output, const char* name)
{
	output << std::setw(5) << "" << std::left << std::setw(14) << name;
	return output;
}

inline std::ostream& operator<<(std::ostream& out, std::ostream&) noexcept
{
	return out;
}

struct Operation
{
	bytecode::Op_code op_code;
	bytecode::Size size;
};

inline Operation fetch_and_decode(std::istream& input)
{
	const auto code = util::portable::read<typename std::underlying_type<bytecode::Op_code>::type>(input);
	return Operation{ static_cast<bytecode::Op_code>(code & 0x3f), static_cast<bytecode::Size>(code >> 6) };
}

void bytecode::disassemble(std::istream& input, std::ostream& output)
{
	using namespace bytecode;
	using namespace util::portable;

	while (input) {
		const auto op = fetch_and_decode(input);
		switch (op.op_code) {
		case Op_code::store: {
			const auto destination = read<Address>(input);
			std::uint64_t value    = 0;
			switch (op.size) {
			case Size::bit_8: value = read<std::uint8_t>(input); break;
			case Size::bit_16: value = read<std::uint16_t>(input); break;
			case Size::bit_32: value = read<std::uint32_t>(input); break;
			case Size::bit_64: value = read<std::uint64_t>(input); break;
			}
			out(output, op.size, "store");
			break;
		}
		case Op_code::load_resource: {
			// const auto destination = ip.read<Address>();
			// const auto index       = ip.read<std::uint32_t>();
			// const auto& resource   = resources.at(index);
			// if (resource.is_type<memory::gc::GC_able<memory::gc::String*>>()) {
			// 	frame.store(destination, resource.get<memory::gc::GC_able<memory::gc::String*>>());
			// } else if (resource.is_type<memory::gc::GC_able<memory::gc::Regex*>>()) {
			// 	frame.store(destination, resource.get<memory::gc::GC_able<memory::gc::Regex*>>());
			// } else {
			// 	// TODO
			// 	BIA_ASSERT(false);
			// }
			break;
		}
		case Op_code::load_from_namespace: {
			// const auto destination = ip.read<Address>();
			// const auto source      = ip.read<Address>();
			// switch (op.size) {
			// case Size::bit_8: frame.store(destination, namespaces[0].load<std::uint8_t>(source)); break;
			// case Size::bit_16: frame.store(destination, namespaces[0].load<std::uint16_t>(source)); break;
			// case Size::bit_32: frame.store(destination, namespaces[0].load<std::uint32_t>(source)); break;
			// case Size::bit_64: frame.store(destination, namespaces[0].load<std::uint64_t>(source)); break;
			// }
			// break;
		}
		case Op_code::copy: {
			const auto destination = read<Address>(input);
			const auto source      = read<Address>(input);
			// switch (op.size) {
			// case Size::bit_8: frame.store(destination, frame.load<std::uint8_t>(source)); break;
			// case Size::bit_16: frame.store(destination, frame.load<std::uint16_t>(source)); break;
			// case Size::bit_32: frame.store(destination, frame.load<std::uint32_t>(source)); break;
			// case Size::bit_64: frame.store(destination, frame.load<std::uint64_t>(source)); break;
			// }
			output << "copy "
			       << "%" << source << ", %" << destination;
			break;
		}
		// case Op_code::add: native_integral_operation<Addition, false>(op, ip, frame); break;
		// case Op_code::fadd: native_floating_operation<Addition>(op, ip, frame); break;
		// case Op_code::sub: native_integral_operation<Subtraction, false>(op, ip, frame); break;
		// case Op_code::fsub: native_floating_operation<Subtraction>(op, ip, frame); break;
		// case Op_code::mul: native_integral_operation<Multiplication, false>(op, ip, frame); break;
		// case Op_code::fmul: native_floating_operation<Multiplication>(op, ip, frame); break;
		// case Op_code::sdiv: native_integral_operation<Division, true>(op, ip, frame); break;
		// case Op_code::udiv: native_integral_operation<Division, false>(op, ip, frame); break;
		// case Op_code::fdiv: native_floating_operation<Division>(op, ip, frame); break;
		// case Op_code::srem: native_integral_operation<Remainder, true>(op, ip, frame); break;
		// case Op_code::urem: native_integral_operation<Remainder, false>(op, ip, frame); break;
		// case Op_code::frem: native_floating_operation<Remainder>(op, ip, frame); break;
		// case Op_code::bitwise_and: native_integral_operation<Bitwise_and, false>(op, ip, frame); break;
		// case Op_code::bitwise_or: native_integral_operation<Bitwise_or, false>(op, ip, frame); break;
		// case Op_code::bitwise_xor: native_integral_operation<Bitwise_xor, false>(op, ip, frame); break;
		// case Op_code::equal: test_register = native_integral_test<Equality, false>(op, ip, frame); break;
		// case Op_code::not_equal: test_register = !native_integral_test<Equality, false>(op, ip, frame); break;
		case Op_code::invoke: {
			const auto function_address = read<Address>(input);
			output << "invoke "
			       << "%" << function_address;
			break;
		}
		case Op_code::test: {
			const auto source = read<Address>(input);
			out(output, "test");
			break;
		}
		case Op_code::jump: {
			const auto offset = read<std::int32_t>(input);
			output << "jump " << offset;
			break;
		}
		case Op_code::jump_true: {
			const auto offset = read<std::int32_t>(input);
			output << "jump_true " << offset;
			break;
		}
		case Op_code::jump_false: {
			const auto offset = read<std::int32_t>(input);
			output << "jump_false " << offset;
			break;
		}
		default: BIA_THROW(error::Code::bad_opcode);
		}
		output << std::endl;
	}
}
