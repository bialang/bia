#include "disassembler.hpp"

#include "op_code.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/portable/stream.hpp>
#include <cstdint>
#include <iomanip>
#include <type_traits>

using namespace bia;

template<typename Type>
inline void constant(std::ostream& output, Type value)
{
	output << std::dec << std::left << std::setw(13) << std::setfill(' ') << value;
}

inline void address(std::ostream& output, bytecode::Address address)
{
	output << "%(0x" << std::hex << std::right << std::setw(8) << std::setfill('0') << address << ")";
}

inline void location(std::ostream& output, std::streamoff offset)
{
	output << "0x" << std::hex << std::right << std::setfill('0') << std::setw(8) << offset;
}

inline void out(std::ostream& output, bytecode::Size size, const char* name)
{
	const char* str = "<00>";
	switch (size) {
	case bytecode::Size::bit_8: str = "<8>"; break;
	case bytecode::Size::bit_16: str = "<16>"; break;
	case bytecode::Size::bit_32: str = "<32>"; break;
	case bytecode::Size::bit_64: str = "<64>"; break;
	}
	output << std::left << std::setfill(' ') << std::setw(5) << str << std::setw(14) << std::setfill(' ')
	       << name;
}

inline void out(std::ostream& output, const char* name)
{
	output << "     " << std::left << std::setw(14) << std::setfill(' ') << name;
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

	std::ios old_state{ nullptr };
	old_state.copyfmt(output);
	const auto final_action = util::finallay([&] { output.copyfmt(old_state); });
	const auto start        = input.tellg();

	while (input) {
		location(output, input.tellg() - start);
		output << ": ";

		const auto op                = fetch_and_decode(input);
		const auto address_operation = [&](const char* name) {
			const auto arg0 = read<Address>(input);
			const auto arg1 = read<Address>(input);
			out(output, op.size, name);
			address(output, arg0);
			output << ", ";
			address(output, arg1);
		};

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
			address(output, destination);
			output << ", ";
			constant(output, value);
			break;
		}
		case Op_code::load_resource: {
			const auto destination = read<Address>(input);
			const auto index       = read<std::uint32_t>(input);
			out(output, "load");
			address(output, destination);
			output << ", ";
			constant(output, index);
			break;
		}
		case Op_code::load_from_namespace: address_operation("load_ns"); break;
		case Op_code::copy: address_operation("copy"); break;
		case Op_code::copy_to_namespace: address_operation("copy_ns"); break;
		case Op_code::add: address_operation("add"); break;
		case Op_code::fadd: address_operation("fadd"); break;
		case Op_code::sub: address_operation("sub"); break;
		case Op_code::fsub: address_operation("fsub"); break;
		case Op_code::mul: address_operation("mul"); break;
		case Op_code::fmul: address_operation("fmul"); break;
		case Op_code::sdiv: address_operation("sdiv"); break;
		case Op_code::udiv: address_operation("udiv"); break;
		case Op_code::fdiv: address_operation("fdiv"); break;
		case Op_code::srem: address_operation("srem"); break;
		case Op_code::urem: address_operation("urem"); break;
		case Op_code::frem: address_operation("frem"); break;
		case Op_code::bitwise_and: address_operation("bitwise_and"); break;
		case Op_code::bitwise_or: address_operation("bitwise_or"); break;
		case Op_code::bitwise_xor: address_operation("bitwise_xor"); break;
		case Op_code::equal: address_operation("equal"); break;
		case Op_code::not_equal: address_operation("not_equal"); break;
		case Op_code::sless_than: address_operation("sless_than"); break;
		case Op_code::uless_than: address_operation("uless_than"); break;
		case Op_code::sless_equal_than: address_operation("sless_equal_than"); break;
		case Op_code::uless_equal_than: address_operation("uless_equal_than"); break;
		case Op_code::sgreater_than: address_operation("sgreater_than"); break;
		case Op_code::ugreater_than: address_operation("ugreater_than"); break;
		case Op_code::sgreater_equal_than: address_operation("sgreater_equal_than"); break;
		case Op_code::ugreater_equal_than: address_operation("ugreater_equal_than"); break;
		case Op_code::invoke: {
			const auto function_address = read<Address>(input);
			out(output, "invoke");
			address(output, function_address);
			break;
		}
		case Op_code::test: {
			const auto source = read<Address>(input);
			out(output, "test");
			address(output, source);
			break;
		}
		case Op_code::jump: {
			const auto offset = read<std::int32_t>(input);
			out(output, "jump");
			location(output, offset + input.tellg());
			break;
		}
		case Op_code::jump_true: {
			const auto offset = read<std::int32_t>(input);
			out(output, "jump_true");
			location(output, offset + input.tellg());
			break;
		}
		case Op_code::jump_false: {
			const auto offset = read<std::int32_t>(input);
			out(output, "jump_false");
			location(output, offset + input.tellg());
			break;
		}
		default: BIA_THROW(error::Code::bad_opcode);
		}
		output << std::endl;
	}
}
