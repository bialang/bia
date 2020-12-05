#include "disassembler.hpp"

#include <bia/bvm/instruction_pointer.hpp>
#include <bia/error/exception.hpp>
#include <bia/member/cast/cast.hpp>
#include <bia/member/function/function.hpp>
#include <bia/member/member.hpp>
#include <bia/member/native/regex.hpp>
#include <bia/member/native/string.hpp>
#include <bia/util/finally.hpp>
#include <iomanip>

inline std::ostream& oo_parameter(bia::bytecode::offset_option option, bia::bvm::instruction_pointer& ip,
                                  std::ostream& output)
{
	using namespace bia::bytecode;

	switch (option) {
	case oo_8: return output << (int) ip.read<std::int8_t>();
	case oo_16: return output << ip.read<std::int16_t>();
	case oo_32: return output << ip.read<std::int32_t>();
	default: BIA_THROW(bia::error::code::bad_offset_option);
	}
}

inline std::ostream& co_parameter(bia::bytecode::constant_option option, bia::bvm::instruction_pointer& ip,
                                  std::ostream& output)
{
	using namespace bia::bytecode;
	switch (option) {
	case co_int_8: return output << '$' << static_cast<int>(ip.read<std::int8_t>());
	case co_uint_8: return output << '$' << static_cast<int>(ip.read<std::uint8_t>());
	case co_int_16: return output << '$' << ip.read<std::int16_t>();
	case co_uint_16: return output << '$' << ip.read<std::uint16_t>();
	case co_int_32: return output << '$' << ip.read<std::int32_t>();
	case co_uint_32: return output << '$' << ip.read<std::uint32_t>();
	case co_int_64: return output << '$' << ip.read<std::int64_t>();
	case co_uint_64: return output << '$' << ip.read<std::uint64_t>();
	case co_float_32: return output << '$' << ip.read<float>();
	case co_float_64: return output << '$' << ip.read<double>();
	case co_test_register: return output << "$tr";
	case co_null: return output << "$null";
	default: BIA_THROW(bia::error::code::bad_constant_option);
	}
}

inline std::ostream& print_resource(const bia::member::member& resource, std::ostream& output)
{
	if (dynamic_cast<const bia::member::native::string*>(&resource)) {
		return output << '"' << static_cast<const bia::member::native::string*>(&resource)->value().get() << '"';
	} else if (dynamic_cast<const bia::member::native::regex*>(&resource)) {
		return output << "regex";
	} else if (dynamic_cast<const bia::member::function::function*>(&resource)) {
		return output << "function";
	}

	return output << "invalid";
}

inline std::ostream& ro_parameter(bia::bytecode::resource_option option, bia::bvm::instruction_pointer& ip,
                                  bia::gc::root& resources, std::ostream& output)
{
	using namespace bia::bytecode;

	switch (option) {
	case ro_8: return print_resource(*resources.at(ip.read<std::uint8_t>()).get(), output);
	case ro_16: return print_resource(*resources.at(ip.read<std::uint16_t>()).get(), output);
	case ro_32: return print_resource(*resources.at(ip.read<std::uint32_t>()).get(), output);
	default: BIA_THROW(bia::error::code::bad_resource_option);
	}
}

inline std::ostream& mso_parameter(bia::bytecode::member_source_option option,
                                   bia::bvm::instruction_pointer& ip, bia::gc::root& resources,
                                   std::ostream& output)
{
	using namespace bia::bytecode;

	constexpr const char* builtins[] = { "list", "range" };

	switch (option) {
	case mso_args_16: return output << 'a' << ip.read<std::uint16_t>();
	case mso_global_16: return output << 'g';
	case mso_resource_16: return print_resource(*resources.at(ip.read<std::uint16_t>()).get(), output);
	case mso_local_16: return output << 'l' << ip.read<std::uint16_t>();
	case mso_args_8: return output << 'a' << (int) ip.read<std::uint8_t>();
	case mso_global_8: return output << 'g';
	case mso_resource_8: return print_resource(*resources.at(ip.read<std::uint8_t>()).get(), output);
	case mso_local_8: return output << 'l' << (int) ip.read<std::uint8_t>();
	case mso_builtin: return output << builtins[(int) ip.read<member::builtin>()];
	default: BIA_THROW(bia::error::code::bad_member_source_option);
	}
}

inline std::ostream& mdo_parameter(bia::bytecode::member_destination_option option,
                                   bia::bvm::instruction_pointer& ip, bia::gc::root& resources,
                                   std::ostream& output)
{
	using namespace bia::bytecode;

	switch (option) {
	case mdo_args_16: return output << 'a' << ip.read<std::uint16_t>();
	case mdo_global_16: return print_resource(*resources.at(ip.read<std::uint16_t>()).get(), output << 'g');
	case mdo_local_16: return output << 'l' << ip.read<std::uint16_t>();
	case mdo_args_8: return output << 'a' << (int) ip.read<std::uint8_t>();
	case mdo_global_8: return print_resource(*resources.at(ip.read<std::uint8_t>()).get(), output << 'g');
	case mdo_local_8: return output << 'l' << (int) ip.read<std::uint8_t>();
	case mdo_push: return output << "push";
	default: BIA_THROW(bia::error::code::bad_member_destination_option);
	}
}

void bia::assembler::disassemble(util::span<const util::byte*> instructions, gc::root& resources,
                                 std::ostream& output)
{
	using namespace bytecode;
	using bia::member::infix_operator;
	using bia::member::self_operator;
	using bia::member::test_operator;

	bvm::instruction_pointer ip{ instructions };
	const auto print_border = [&output] {
		constexpr auto disassembly_padding = "=====================";
		output << disassembly_padding << "DISASSEMBLY" << disassembly_padding << '\n';
	};
	const auto finally = util::make_finally([&] {
		print_border();
		output.flush();
	});

	print_border();

	while (ip) {
		output << "0x" << std::hex << std::setw(8) << std::setfill('0') << ip.cursor() << ": " << std::setw(10)
		       << std::setfill(' ') << std::left;
		const auto op_code = ip.next_op_code();

		switch (to_op_code_base(op_code)) {
		case oc_operator: {
			const auto options =
			  parse_options<oc_operator, member_source_option, member_source_option, member_destination_option>(
			    op_code);

			mso_parameter(std::get<0>(options), ip, resources, output << "op");
			mso_parameter(std::get<1>(options), ip, resources, output << ", ");
			mdo_parameter(std::get<2>(options), ip, resources,
			              output << ", " << (int) ip.read<infix_operator>() << ", ");

			break;
		}
		case oc_get: {
			const auto options =
			  parse_options<oc_get, member_source_option, resource_option, member_destination_option>(op_code);

			mso_parameter(std::get<0>(options), ip, resources, output << "get");
			ro_parameter(std::get<1>(options), ip, resources, output << ", ");
			mdo_parameter(std::get<2>(options), ip, resources, output << ", ");

			break;
		}
		case oc_test: {
			const auto options = parse_options<oc_test, member_source_option, member_source_option>(op_code);
			const auto op      = ip.read<test_operator>();

			mso_parameter(std::get<0>(options), ip, resources, output << "test");
			mso_parameter(std::get<1>(options), ip, resources, output << ", ");

			output << ", " << (int) op;

			break;
		}
		case oc_instantiate: {
			const auto options = parse_options<oc_instantiate, constant_option, member_destination_option>(op_code);

			co_parameter(std::get<0>(options), ip, output << "inst");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", ");

			break;
		}
		case oc_invoke: {
			const auto options = parse_options<oc_invoke, member_source_option, member_destination_option>(op_code);

			mso_parameter(std::get<0>(options), ip, resources, output << "invoke");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", ");

			break;
		}
		case oc_refer: {
			const auto options = parse_options<oc_refer, member_source_option, member_destination_option>(op_code);

			mso_parameter(std::get<0>(options), ip, resources, output << "refer");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", ");

			break;
		}
		case oc_clone: {
			const auto options = parse_options<oc_clone, member_source_option, member_destination_option>(op_code);

			mso_parameter(std::get<0>(options), ip, resources, output << "clone");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", ");

			break;
		}
		case oc_copy: {
			const auto options = parse_options<oc_copy, member_source_option, member_destination_option>(op_code);

			mso_parameter(std::get<0>(options), ip, resources, output << "copy");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", ");

			break;
		}
		case oc_self_operator: {
			const auto options =
			  parse_options<oc_self_operator, member_source_option, member_destination_option>(op_code);
			const auto op = ip.read<self_operator>();

			mso_parameter(std::get<0>(options), ip, resources, output << "self_op");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", " << (int) op << ", ");

			break;
		}
		case oc_import: {
			const auto options = parse_options<oc_import, resource_option, member_destination_option>(op_code);

			ro_parameter(std::get<0>(options), ip, resources, output << "import");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", ");

			break;
		}
		case oc_initiate: {
			const auto options = parse_options<oc_import, resource_option, member_destination_option>(op_code);

			ro_parameter(std::get<0>(options), ip, resources, output << "initiate");
			mdo_parameter(std::get<1>(options), ip, resources, output << ", ");

			break;
		}
		case oc_jump: {
			oo_parameter(std::get<0>(parse_options<oc_jump, offset_option>(op_code)), ip, output << "jmp");

			break;
		}
		case oc_jump_true: {
			oo_parameter(std::get<0>(parse_options<oc_jump, offset_option>(op_code)), ip, output << "jmpt");

			break;
		}
		case oc_jump_false: {
			oo_parameter(std::get<0>(parse_options<oc_jump, offset_option>(op_code)), ip, output << "jmpf");

			break;
		}
		case oc_name: {
			ro_parameter(std::get<0>(parse_options<oc_name, resource_option>(op_code)), ip, resources,
			             output << "name");

			break;
		}
		case oc_return: {
			mso_parameter(std::get<0>(parse_options<oc_return, member_source_option>(op_code)), ip, resources,
			              output << "ret3");

			break;
		}
		case oc_return_void: output << "ret"; break;
		case oc_invert: output << "invert"; break;
		case oc_prep_call: output << "prep_call"; break;
		default: output << "<invalid>\n"; return;
		}

		output << '\n';
	}
}
