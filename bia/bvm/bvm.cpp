#include "bvm.hpp"

#include "instruction_pointer.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
#include <bia/exception/nullpointer.hpp>
#include <bia/exception/opcode.hpp>
#include <bia/member/function/function.hpp>
#include <bia/member/invoke_context.hpp>
#include <bia/member/native/key_value_pair.hpp>
#include <bia/util/finally.hpp>
#include <type_traits>
#include <typeinfo>
using namespace bia::bvm;

template<typename Type>
inline typename std::enable_if<std::is_base_of<bia::member::member, Type>::value, Type*>::type
    member_pointer(bia::member::member* element)
{
	if (const auto ptr = dynamic_cast<Type*>(element)) {
		return ptr;
	}

	BIA_THROW(bia::exception::nullpointer, "nullpointer member access");
}

template<>
inline bia::member::member* member_pointer<bia::member::member>(bia::member::member* element)
{
	if (element) {
		return element;
	}

	BIA_THROW(bia::exception::nullpointer, "nullpointer member access");
}

inline std::int32_t oo_parameter(bia::bytecode::offset_option option, instruction_pointer& ip)
{
	using namespace bia::bytecode;

	switch (option) {
	case oo_8: return ip.read<std::int8_t>();
	case oo_16: return ip.read<std::int16_t>();
	case oo_32: return ip.read<std::int32_t>();
	default: break;
	}

	BIA_IMPLEMENTATION_ERROR("not implemented");
}

inline bia::gc::gcable<bia::member::member> co_parameter(bia::bytecode::constant_option option,
                                                         instruction_pointer& ip, bia::gc::gc& gc,
                                                         bia::member::member::test_type test_register)
{
	using namespace bia::bytecode;

	switch (option) {
	case co_int_8: return bia::creator::create(gc, ip.read<std::int8_t>());
	case co_int_16: return bia::creator::create(gc, ip.read<std::int16_t>());
	case co_int_32: return bia::creator::create(gc, ip.read<std::int32_t>());
	case co_int_64: return bia::creator::create(gc, ip.read<std::int64_t>());
	case co_double: return bia::creator::create(gc, ip.read<double>());
	case co_test_register: return bia::creator::create(gc, test_register);
	case co_null: return {};
	default: break;
	}

	BIA_IMPLEMENTATION_ERROR("not implemented");
}

inline bia::member::member* ro_parameter(bia::bytecode::resource_option option, instruction_pointer& ip,
                                         bia::gc::root& resources)
{
	using namespace bia::bytecode;

	switch (option) {
	case ro_8: return resources.at(ip.read<std::uint8_t>()).get();
	case ro_16: return resources.at(ip.read<std::uint16_t>()).get();
	case ro_32: return resources.at(ip.read<std::uint32_t>()).get();
	default: break;
	}

	BIA_IMPLEMENTATION_ERROR("not implemented");
}

inline bia::member::member* mso_parameter(bia::bytecode::member_source_option option, instruction_pointer& ip,
                                          context& context, bia::member::native::dict& globals,
                                          bia::gc::stack_view& stack, bia::gc::root& resources)
{
	using namespace bia::bytecode;

	switch (option) {
	case mso_args_16: return stack.arg_at(ip.read<std::uint16_t>());
	case mso_global_16:
		return globals
		    .get(*member_pointer<bia::member::native::string>(resources.at(ip.read<std::uint16_t>()).get()))
		    .peek();
	case mso_local_16: return stack.local_at(ip.read<std::uint16_t>());
	case mso_resource_16: return resources.at(ip.read<std::uint16_t>()).get();
	case mso_args_8: return stack.arg_at(ip.read<std::uint8_t>());
	case mso_global_8:
		return globals
		    .get(*member_pointer<bia::member::native::string>(resources.at(ip.read<std::uint8_t>()).get()))
		    .peek();
	case mso_local_8: return stack.local_at(ip.read<std::uint8_t>());
	case mso_resource_8: return resources.at(ip.read<std::uint8_t>()).get();
	case mso_builtin: return context.builtin(ip.read<member::builtin>());
	default: break;
	}

	BIA_IMPLEMENTATION_ERROR("not implemented");
}

template<typename Source>
inline void mdo_parameter(bia::bytecode::member_destination_option option, instruction_pointer& ip,
                          bia::gc::stack_view& stack, bia::gc::token& token, Source&& source)
{
	using namespace bia::bytecode;

	switch (option) {
	case mdo_args_16: token.set(stack.arg_at(ip.read<std::uint16_t>()), std::forward<Source>(source)); break;
	case mdo_local_16:
		token.set(stack.local_at(ip.read<std::uint16_t>()), std::forward<Source>(source));
		break;
	case mdo_args_8: token.set(stack.arg_at(ip.read<std::uint8_t>()), std::forward<Source>(source)); break;
	case mdo_local_8: token.set(stack.local_at(ip.read<std::uint8_t>()), std::forward<Source>(source)); break;
	case mdo_push: token.set(stack.push(), std::forward<Source>(source)); break;
	default: BIA_IMPLEMENTATION_ERROR("not implemented");
	}
}

inline bia::gc::gcable<bia::member::member> make_key_value_pair(bia::member::native::string* key,
                                                                bia::member::member* value)
{
	return bia::gc::gc::active_gc()->construct<bia::member::native::key_value_pair>(key, value);
}

bia::gc::gcable<bia::member::member>
    bvm::execute(context& context, util::span<const util::byte*> instructions, gc::root& resources)
{
	auto token = context.gc().register_thread(64);
	auto stack = token->stack_view();

	return execute(context, instructions, resources, stack, *token);
}

bia::gc::gcable<bia::member::member> bvm::execute(context& context,
                                                  util::span<const util::byte*> instructions,
                                                  gc::root& resources, gc::stack_view& stack,
                                                  gc::token& token)
{
	using namespace bytecode;
	using flag = bia::member::member::flag;
	using bia::member::infix_operator;
	using bia::member::self_operator;
	using bia::member::test_operator;

	instruction_pointer ip{ instructions.begin(), instructions.end() };
	bia::member::member::test_type test_register = 0;
	auto& gc                                     = context.gc();
	auto& globals                                = context.symbols();
	auto& loader                                 = context.loader();

	while (ip) {
		const auto op_code = ip.next_op_code();

		switch (to_op_code_base(op_code)) {
		case oc_operator: {
			const auto options = parse_options<oc_operator, member_source_option, member_source_option,
			                                   member_destination_option>(op_code);
			const auto left    = member_pointer<bia::member::member>(
                mso_parameter(std::get<0>(options), ip, context, globals, stack, resources));
			const auto right = member_pointer<bia::member::member>(
			    mso_parameter(std::get<1>(options), ip, context, globals, stack, resources));
			const auto op = ip.read<infix_operator>();

			mdo_parameter(std::get<2>(options), ip, stack, token, left->operation(*right, op));

			break;
		}
		case oc_get: {
			const auto options =
			    parse_options<oc_get, member_source_option, resource_option, member_destination_option>(
			        op_code);
			const auto src = member_pointer<bia::member::member>(
			    mso_parameter(std::get<0>(options), ip, context, globals, stack, resources));
			const auto name = member_pointer<bia::member::native::string>(
			    ro_parameter(std::get<1>(options), ip, resources));

			mdo_parameter(std::get<2>(options), ip, stack, token, src->get(*name));

			break;
		}
		case oc_test: {
			const auto options = parse_options<oc_test, member_source_option, member_source_option>(op_code);
			const auto op      = ip.read<test_operator>();
			const auto left    = mso_parameter(std::get<0>(options), ip, context, globals, stack, resources);
			const auto right   = mso_parameter(std::get<1>(options), ip, context, globals, stack, resources);

			test_register = member_pointer<bia::member::member>(left)->test(
			    op, *member_pointer<bia::member::member>(right));

			break;
		}
		case oc_instantiate: {
			const auto options =
			    parse_options<oc_instantiate, constant_option, member_destination_option>(op_code);

			mdo_parameter(std::get<1>(options), ip, stack, token,
			              co_parameter(std::get<0>(options), ip, gc, test_register));

			break;
		}
		case oc_invoke: {
			const auto options =
			    parse_options<oc_invoke, member_source_option, member_destination_option>(op_code);
			const auto caller = member_pointer<bia::member::member>(
			    mso_parameter(std::get<0>(options), ip, context, globals, stack, resources));
			connector::parameters params{ stack.make_call_frame() };
			bia::member::invoke_context ic{ context, resources, token };

			mdo_parameter(std::get<1>(options), ip, stack, token, caller->invoke(params, ic));

			break;
		}
		case oc_refer: {
			const auto options =
			    parse_options<oc_refer, member_source_option, member_destination_option>(op_code);
			const auto src = mso_parameter(std::get<0>(options), ip, context, globals, stack, resources);

			mdo_parameter(std::get<1>(options), ip, stack, token, src);

			break;
		}
		case oc_clone: {
			const auto options =
			    parse_options<oc_clone, member_source_option, member_destination_option>(op_code);
			const auto src = mso_parameter(std::get<0>(options), ip, context, globals, stack, resources);

			if (src && src->flags() & bia::member::member::flag_clone_is_copy) {
				mdo_parameter(std::get<1>(options), ip, stack, token, src->copy());
			} else {
				mdo_parameter(std::get<1>(options), ip, stack, token, src);
			}

			break;
		}
		case oc_copy: {
			const auto options =
			    parse_options<oc_copy, member_source_option, member_destination_option>(op_code);
			const auto src = mso_parameter(std::get<0>(options), ip, context, globals, stack, resources);

			if (src) {
				mdo_parameter(std::get<1>(options), ip, stack, token, src->copy());
			} else {
				mdo_parameter(std::get<1>(options), ip, stack, token, src);
			}

			break;
		}
		case oc_self_operator: {
			const auto options =
			    parse_options<oc_self_operator, member_source_option, member_destination_option>(op_code);
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer<bia::member::member>(
			    mso_parameter(std::get<0>(options), ip, context, globals, stack, resources));

			mdo_parameter(std::get<1>(options), ip, stack, token, src->self_operation(op));

			break;
		}
		case oc_import: {
			const auto options =
			    parse_options<oc_import, resource_option, member_destination_option>(op_code);
			const auto name = member_pointer<bia::member::native::string>(
			    ro_parameter(std::get<0>(options), ip, resources));

			mdo_parameter(std::get<1>(options), ip, stack, token, loader.load(name).get());

			break;
		}
		case oc_initiate: {
			const auto options =
			    parse_options<oc_initiate, resource_option, member_destination_option>(op_code);
			const auto function = member_pointer<bia::member::function::function>(
			    ro_parameter(std::get<0>(options), ip, resources));

			mdo_parameter(std::get<1>(options), ip, stack, token, function->initiate(stack));

			break;
		}
		case oc_jump: {
			const auto offset = oo_parameter(std::get<0>(parse_options<oc_jump, offset_option>(op_code)), ip);

			ip += offset;

			break;
		}
		case oc_jump_true: {
			const auto offset = oo_parameter(std::get<0>(parse_options<oc_jump, offset_option>(op_code)), ip);

			if (test_register) {
				ip += offset;
			}

			break;
		}
		case oc_jump_false: {
			const auto offset = oo_parameter(std::get<0>(parse_options<oc_jump, offset_option>(op_code)), ip);

			if (!test_register) {
				ip += offset;
			}

			break;
		}
		case oc_name: {
			const auto options = parse_options<oc_name, resource_option>(op_code);
			const auto name    = member_pointer<bia::member::native::string>(
                ro_parameter(std::get<0>(options), ip, resources));
			auto& src = stack.last_push();

			stack.mark_kwarg();
			token.set(src, make_key_value_pair(name, src));

			break;
		}
		case oc_return:
			return mso_parameter(std::get<0>(parse_options<oc_return, member_source_option>(op_code)), ip,
			                     context, globals, stack, resources);
		case oc_return_void: return {};
		case oc_invert: test_register = !test_register; break;
		case oc_prep_call: stack.prep_call(); break;
		default: BIA_THROW(exception::opcode, "invalid opcode");
		}
	}

	return {};
}
