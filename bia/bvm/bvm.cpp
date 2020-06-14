#include "bvm.hpp"

#include "instruction_pointer.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
#include <bia/exception/nullpointer.hpp>
#include <bia/exception/opcode.hpp>
#include <bia/gc/gcable.hpp>
#include <bia/gc/stack_view.hpp>
#include <bia/gc/token.hpp>
#include <bia/member/member.hpp>
#include <bia/member/native/key_value_pair.hpp>
#include <bia/util/finally.hpp>
#include <type_traits>

using namespace bia::bvm;

template<typename Pointer>
inline typename std::enable_if<
    std::is_same<bia::gc::object::pointer<bia::member::member>, Pointer>::value ||
        std::is_same<const bia::gc::object::immutable_pointer<bia::member::member>, Pointer>::value,
    bia::member::member*>::type
    member_pointer(Pointer& element)
{
	if (const auto ptr = element.get()) {
		return static_cast<bia::member::member*>(ptr);
	}

	BIA_THROW(bia::exception::nullpointer, "nullpointer member access");
}

inline bia::member::member* member_pointer(bia::member::member* element)
{
	if (element) {
		return element;
	}

	BIA_THROW(bia::exception::nullpointer, "nullpointer member access");
}

inline bia::member::native::string*
    string_pointer(bia::gc::object::immutable_pointer<bia::member::member> element)
{
	if (const auto ptr = dynamic_cast<bia::member::native::string*>(element.get())) {
		return ptr;
	}

	BIA_THROW(bia::exception::nullpointer, "nullpointer string access");
}

inline bia::gc::gcable<bia::member::member> make_key_value_pair(bia::member::native::string* key,
                                                                bia::member::member* value)
{
	return bia::gc::gc::active_gc()
	    ->construct<bia::member::native::key_value_pair>(key, value)
	    .template to<bia::member::member>();
}

void bvm::execute(context& context, util::span<const util::byte*> instructions, gc::root& resources)
{
	using namespace bytecode;
	using flag = bia::member::member::flag;
	using bia::member::infix_operator;
	using bia::member::self_operator;
	using bia::member::test_operator;

	instruction_pointer ip{ instructions.begin(), instructions.end() };
	bia::member::member::test_type test_register{ 10 };
	auto& gc      = context.gc();
	auto& globals = context.symbols();
	auto& loader  = context.loader();
	auto token    = gc.register_thread(64);
	auto stack    = token->stack_view();

	while (ip) {
		const auto op_code = ip.next_op_code();

		switch (op_code) {
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_local_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_local_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_global_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_8 * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_local_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_local_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_8): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_16): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_resource_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_8): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_16): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_local_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_8 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_8 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_8 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_16 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_16 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_16 * mdo_count -
		      mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_global_16 * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_8): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_16): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_16): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_global_8): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_16): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_global_16): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_args * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_8 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_8): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_local_16): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_global_16): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_8 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_resource_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_local_16 * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_8): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_global_8): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_local_16): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_global_16): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_global_16 * mdo_count - mdo_tos): {
			const auto left = member_pointer(stack.tos());
			const auto right =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto op = ip.read<infix_operator>();
			auto& dest    = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_args * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_args * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_args * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_args * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_args * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_8): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_tos * mdo_count - mdo_local_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_tos * mdo_count - mdo_global_16): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_operator - mso_tos * mso_count * mdo_count - mso_tos * mdo_count - mdo_tos): {
			const auto left  = member_pointer(stack.tos());
			const auto right = member_pointer(stack.tos());
			const auto op    = ip.read<infix_operator>();
			auto& dest       = stack.push();

			token->set(dest, left->operation(*right, op));

			break;
		}
		case (oc_instantiate - co_null * mdo_count - mdo_local_8): {
			const auto constant = nullptr;

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_null * mdo_count - mdo_global_8): {
			const auto constant = nullptr;

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_null * mdo_count - mdo_local_16): {
			const auto constant = nullptr;

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_null * mdo_count - mdo_global_16): {
			const auto constant = nullptr;

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_null * mdo_count - mdo_tos): {
			const auto constant = nullptr;

			token->set(stack.push(), creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_test_register * mdo_count - mdo_local_8): {
			const auto constant = test_register;

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_test_register * mdo_count - mdo_global_8): {
			const auto constant = test_register;

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_test_register * mdo_count - mdo_local_16): {
			const auto constant = test_register;

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_test_register * mdo_count - mdo_global_16): {
			const auto constant = test_register;

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_test_register * mdo_count - mdo_tos): {
			const auto constant = test_register;

			token->set(stack.push(), creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_double * mdo_count - mdo_local_8): {
			const auto constant = ip.read<double>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_double * mdo_count - mdo_global_8): {
			const auto constant = ip.read<double>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_double * mdo_count - mdo_local_16): {
			const auto constant = ip.read<double>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_double * mdo_count - mdo_global_16): {
			const auto constant = ip.read<double>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_double * mdo_count - mdo_tos): {
			const auto constant = ip.read<double>();

			token->set(stack.push(), creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_64 * mdo_count - mdo_local_8): {
			const auto constant = ip.read<std::int64_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_64 * mdo_count - mdo_global_8): {
			const auto constant = ip.read<std::int64_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_64 * mdo_count - mdo_local_16): {
			const auto constant = ip.read<std::int64_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_64 * mdo_count - mdo_global_16): {
			const auto constant = ip.read<std::int64_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_64 * mdo_count - mdo_tos): {
			const auto constant = ip.read<std::int64_t>();

			token->set(stack.push(), creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_32 * mdo_count - mdo_local_8): {
			const auto constant = ip.read<std::int32_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_32 * mdo_count - mdo_global_8): {
			const auto constant = ip.read<std::int32_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_32 * mdo_count - mdo_local_16): {
			const auto constant = ip.read<std::int32_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_32 * mdo_count - mdo_global_16): {
			const auto constant = ip.read<std::int32_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_32 * mdo_count - mdo_tos): {
			const auto constant = ip.read<std::int32_t>();

			token->set(stack.push(), creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_16 * mdo_count - mdo_local_8): {
			const auto constant = ip.read<std::int16_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_16 * mdo_count - mdo_global_8): {
			const auto constant = ip.read<std::int16_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_16 * mdo_count - mdo_local_16): {
			const auto constant = ip.read<std::int16_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_16 * mdo_count - mdo_global_16): {
			const auto constant = ip.read<std::int16_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_16 * mdo_count - mdo_tos): {
			const auto constant = ip.read<std::int16_t>();

			token->set(stack.push(), creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_8 * mdo_count - mdo_local_8): {
			const auto constant = ip.read<std::int8_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_8 * mdo_count - mdo_global_8): {
			const auto constant = ip.read<std::int8_t>();

			token->set(stack.local_at(ip.read<std::uint8_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_8 * mdo_count - mdo_local_16): {
			const auto constant = ip.read<std::int8_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_8 * mdo_count - mdo_global_16): {
			const auto constant = ip.read<std::int8_t>();

			token->set(stack.local_at(ip.read<std::uint16_t>()),
			           creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_instantiate - co_int_8 * mdo_count - mdo_tos): {
			const auto constant = ip.read<std::int8_t>();

			token->set(stack.push(), creator::create(constant).to<bia::member::member>());

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_local_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.tos())
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_global_8): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.tos())
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_local_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.tos())
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_global_16): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.tos())
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_tos): {
			const auto count  = ip.read<std::uint8_t>();
			const auto kwargs = ip.read<std::uint8_t>();
			auto result       = member_pointer(stack.tos())
			                  ->invoke(connector::parameters{ stack.frame(count), count, kwargs });

			stack.drop(count);
			token->set(stack.push(), std::move(result));

			break;
		}
		case (oc_refer - mso_resource_8 * mdo_count - mdo_local_8): {
			auto& src = resources.at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_8 * mdo_count - mdo_global_8): {
			auto& src = resources.at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_8 * mdo_count - mdo_local_16): {
			auto& src = resources.at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_8 * mdo_count - mdo_global_16): {
			auto& src = resources.at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_8 * mdo_count - mdo_tos): {
			auto& src = resources.at(ip.read<std::uint8_t>());

			token->set(stack.push(), src);

			break;
		}
		case (oc_refer - mso_local_8 * mdo_count - mdo_local_8): {
			auto& src = stack.local_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_local_8 * mdo_count - mdo_global_8): {
			auto& src = stack.local_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_local_8 * mdo_count - mdo_local_16): {
			auto& src = stack.local_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_local_8 * mdo_count - mdo_global_16): {
			auto& src = stack.local_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_local_8 * mdo_count - mdo_tos): {
			auto& src = stack.local_at(ip.read<std::uint8_t>());

			token->set(stack.push(), src);

			break;
		}
		case (oc_refer - mso_global_8 * mdo_count - mdo_local_8): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_global_8 * mdo_count - mdo_global_8): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_global_8 * mdo_count - mdo_local_16): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_global_8 * mdo_count - mdo_global_16): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_global_8 * mdo_count - mdo_tos): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())));

			token->set(stack.push(), src);

			break;
		}
		case (oc_refer - mso_resource_16 * mdo_count - mdo_local_8): {
			auto& src = resources.at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_16 * mdo_count - mdo_global_8): {
			auto& src = resources.at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_16 * mdo_count - mdo_local_16): {
			auto& src = resources.at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_16 * mdo_count - mdo_global_16): {
			auto& src = resources.at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_resource_16 * mdo_count - mdo_tos): {
			auto& src = resources.at(ip.read<std::uint16_t>());

			token->set(stack.push(), src);

			break;
		}
		case (oc_refer - mso_local_16 * mdo_count - mdo_local_8): {
			auto& src = stack.local_at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_local_16 * mdo_count - mdo_global_8): {
			auto& src = stack.local_at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_local_16 * mdo_count - mdo_local_16): {
			auto& src = stack.local_at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_local_16 * mdo_count - mdo_global_16): {
			auto& src = stack.local_at(ip.read<std::uint16_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_local_16 * mdo_count - mdo_tos): {
			auto& src = stack.local_at(ip.read<std::uint16_t>());

			token->set(stack.push(), src);

			break;
		}
		case (oc_refer - mso_global_16 * mdo_count - mdo_local_8): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_global_16 * mdo_count - mdo_global_8): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_global_16 * mdo_count - mdo_local_16): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_global_16 * mdo_count - mdo_global_16): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_global_16 * mdo_count - mdo_tos): {
			auto src = globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())));

			token->set(stack.push(), src);

			break;
		}
		case (oc_refer - mso_args * mdo_count - mdo_local_8): {
			auto& src = stack.arg_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_args * mdo_count - mdo_global_8): {
			auto& src = stack.arg_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_args * mdo_count - mdo_local_16): {
			auto& src = stack.arg_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_args * mdo_count - mdo_global_16): {
			auto& src = stack.arg_at(ip.read<std::uint8_t>());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_args * mdo_count - mdo_tos): {
			auto& src = stack.arg_at(ip.read<std::uint8_t>());

			token->set(stack.push(), src);

			break;
		}
		case (oc_refer - mso_tos * mdo_count - mdo_local_8): {
			auto& src = stack.tos();

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_tos * mdo_count - mdo_global_8): {
			auto& src = stack.tos();

			token->set(stack.local_at(ip.read<std::uint8_t>()), src);

			break;
		}
		case (oc_refer - mso_tos * mdo_count - mdo_local_16): {
			auto& src = stack.tos();

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_tos * mdo_count - mdo_global_16): {
			auto& src = stack.tos();

			token->set(stack.local_at(ip.read<std::uint16_t>()), src);

			break;
		}
		case (oc_refer - mso_tos * mdo_count - mdo_tos): {
			auto& src = stack.tos();

			token->set(stack.push(), src);

			break;
		}
		case (oc_clone - mso_resource_8 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_8 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_8 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_8 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_8 * mdo_count - mdo_tos): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_clone - mso_local_8 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_8 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_8 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_8 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_8 * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_clone - mso_global_8 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_8 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_8 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_8 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_8 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_clone - mso_resource_16 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_16 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_16 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_16 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_resource_16 * mdo_count - mdo_tos): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_clone - mso_local_16 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_16 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_16 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_16 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_local_16 * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_clone - mso_global_16 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_16 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_16 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_16 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_global_16 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_clone - mso_args * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_args * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_args * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_args * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_args * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_clone - mso_tos * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.tos());

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_tos * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.tos());

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint8_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_tos * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.tos());

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_tos * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.tos());

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());
			} else {
				token->set(stack.local_at(ip.read<std::uint16_t>()), src);
			}

			break;
		}
		case (oc_clone - mso_tos * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.tos());

			if (src->flags() & flag::flag_clone_is_copy) {
				token->set(stack.push(), src->copy());
			} else {
				token->set(stack.push(), src);
			}

			break;
		}
		case (oc_copy - mso_resource_8 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_8 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_8 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_8 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_8 * mdo_count - mdo_tos): {
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_copy - mso_local_8 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_8 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_8 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_8 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_8 * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_copy - mso_global_8 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_8 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_8 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_8 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_8 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_copy - mso_resource_16 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_16 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_16 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_16 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_resource_16 * mdo_count - mdo_tos): {
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_copy - mso_local_16 * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_16 * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_16 * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_16 * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_local_16 * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_copy - mso_global_16 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_16 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_16 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_16 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_global_16 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_copy - mso_args * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_args * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_args * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_args * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_args * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_copy - mso_tos * mdo_count - mdo_local_8): {
			const auto src = member_pointer(stack.tos());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_tos * mdo_count - mdo_global_8): {
			const auto src = member_pointer(stack.tos());

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_tos * mdo_count - mdo_local_16): {
			const auto src = member_pointer(stack.tos());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_tos * mdo_count - mdo_global_16): {
			const auto src = member_pointer(stack.tos());

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->copy());

			break;
		}
		case (oc_copy - mso_tos * mdo_count - mdo_tos): {
			const auto src = member_pointer(stack.tos());

			token->set(stack.push(), src->copy());

			break;
		}
		case (oc_self_operator - mso_resource_8 * mdo_count - mdo_local_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_8 * mdo_count - mdo_global_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_8 * mdo_count - mdo_local_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_8 * mdo_count - mdo_global_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_8 * mdo_count - mdo_tos): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));
			auto& dest     = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_8 * mdo_count - mdo_local_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_8 * mdo_count - mdo_global_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_8 * mdo_count - mdo_local_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_8 * mdo_count - mdo_global_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_8 * mdo_count - mdo_tos): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_8 * mdo_count - mdo_local_8): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_8 * mdo_count - mdo_global_8): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_8 * mdo_count - mdo_local_16): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_8 * mdo_count - mdo_global_16): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_8 * mdo_count - mdo_tos): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			auto& dest = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_16 * mdo_count - mdo_local_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_16 * mdo_count - mdo_global_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_16 * mdo_count - mdo_local_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_16 * mdo_count - mdo_global_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_resource_16 * mdo_count - mdo_tos): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));
			auto& dest     = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_16 * mdo_count - mdo_local_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_16 * mdo_count - mdo_global_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_16 * mdo_count - mdo_local_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_16 * mdo_count - mdo_global_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_local_16 * mdo_count - mdo_tos): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			auto& dest     = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_16 * mdo_count - mdo_local_8): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_16 * mdo_count - mdo_global_8): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_16 * mdo_count - mdo_local_16): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_16 * mdo_count - mdo_global_16): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			auto& dest = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_global_16 * mdo_count - mdo_tos): {
			const auto op = ip.read<self_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			auto& dest = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_args * mdo_count - mdo_local_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_args * mdo_count - mdo_global_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_args * mdo_count - mdo_local_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_args * mdo_count - mdo_global_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_args * mdo_count - mdo_tos): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			auto& dest     = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_tos * mdo_count - mdo_local_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.tos());
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_tos * mdo_count - mdo_global_8): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.tos());
			auto& dest     = stack.local_at(ip.read<std::uint8_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_tos * mdo_count - mdo_local_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.tos());
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_tos * mdo_count - mdo_global_16): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.tos());
			auto& dest     = stack.local_at(ip.read<std::uint16_t>());

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_self_operator - mso_tos * mdo_count - mdo_tos): {
			const auto op  = ip.read<self_operator>();
			const auto src = member_pointer(stack.tos());
			auto& dest     = stack.push();

			token->set(dest, src->self_operation(op));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_resource_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_local_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_global_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_resource_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_local_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_global_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_args): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_resource_8 * mso_count - mso_tos): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_resource_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_local_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_global_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_resource_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_local_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_global_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_args): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_local_8 * mso_count - mso_tos): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_resource_8): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_local_8): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_global_8): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_resource_16): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_local_16): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_global_16): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_args): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_global_8 * mso_count - mso_tos): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_resource_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_local_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_global_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_resource_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_local_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_global_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_args): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_resource_16 * mso_count - mso_tos): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(resources.at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_resource_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_local_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_global_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_resource_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_local_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_global_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_args): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_local_16 * mso_count - mso_tos): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.local_at(ip.read<std::uint16_t>()));

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_resource_8): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_local_8): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_global_8): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_resource_16): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_local_16): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_global_16): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_args): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_global_16 * mso_count - mso_tos): {
			const auto op = ip.read<test_operator>();
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_resource_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_local_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_global_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_resource_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_local_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_global_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_args): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_args * mso_count - mso_tos): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_resource_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_local_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_global_8): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>())))));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_resource_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(op, *member_pointer(resources.at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_local_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(op, *member_pointer(stack.local_at(ip.read<std::uint16_t>())));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_global_16): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(
			    op, *member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>())))));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_args): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(op, *member_pointer(stack.arg_at(ip.read<std::uint8_t>())));

			break;
		}
		case (oc_test - mso_tos * mso_count - mso_tos): {
			const auto op  = ip.read<test_operator>();
			const auto src = member_pointer(stack.tos());

			test_register = src->test(op, *member_pointer(stack.tos()));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_8 * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_resource_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(resources.at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_local_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.local_at(ip.read<std::uint16_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_global_16 * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_args * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.arg_at(ip.read<std::uint8_t>()));
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_32 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_32 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_32 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_16 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_16 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_16 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_8): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_8): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_8 * mdo_count - mdo_local_16): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_8 * mdo_count - mdo_global_16): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), src->get(*name));

			break;
		}
		case (oc_get - mso_tos * ro_count * mdo_count - ro_8 * mdo_count - mdo_tos): {
			const auto src  = member_pointer(stack.tos());
			const auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), src->get(*name));

			break;
		}
		case (oc_import - ro_32 * mdo_count - mdo_local_8): {
			auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_32 * mdo_count - mdo_global_8): {
			auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_32 * mdo_count - mdo_local_16): {
			auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_32 * mdo_count - mdo_global_16): {
			auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_32 * mdo_count - mdo_tos): {
			auto name = string_pointer(resources.at(ip.read<std::uint32_t>()));

			token->set(stack.push(), loader.load(name).get());

			break;
		}
		case (oc_import - ro_16 * mdo_count - mdo_local_8): {
			auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_16 * mdo_count - mdo_global_8): {
			auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_16 * mdo_count - mdo_local_16): {
			auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_16 * mdo_count - mdo_global_16): {
			auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_16 * mdo_count - mdo_tos): {
			auto name = string_pointer(resources.at(ip.read<std::uint16_t>()));

			token->set(stack.push(), loader.load(name).get());

			break;
		}
		case (oc_import - ro_8 * mdo_count - mdo_local_8): {
			auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_8 * mdo_count - mdo_global_8): {
			auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint8_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_8 * mdo_count - mdo_local_16): {
			auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_8 * mdo_count - mdo_global_16): {
			auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.local_at(ip.read<std::uint16_t>()), loader.load(name).get());

			break;
		}
		case (oc_import - ro_8 * mdo_count - mdo_tos): {
			auto name = string_pointer(resources.at(ip.read<std::uint8_t>()));

			token->set(stack.push(), loader.load(name).get());

			break;
		}
		case (oc_jump - oo_32): {
			const auto offset = ip.read<std::int32_t>();

			ip += offset;

			break;
		}
		case (oc_jump - oo_16): {
			const auto offset = ip.read<std::int16_t>();

			ip += offset;

			break;
		}
		case (oc_jump - oo_8): {
			const auto offset = ip.read<std::int8_t>();

			ip += offset;

			break;
		}
		case (oc_jump_true - oo_32): {
			const auto offset = ip.read<std::int32_t>();

			if (test_register) {
				ip += offset;
			}

			break;
		}
		case (oc_jump_true - oo_16): {
			const auto offset = ip.read<std::int16_t>();

			if (test_register) {
				ip += offset;
			}

			break;
		}
		case (oc_jump_true - oo_8): {
			const auto offset = ip.read<std::int8_t>();

			if (test_register) {
				ip += offset;
			}

			break;
		}
		case (oc_jump_false - oo_32): {
			const auto offset = ip.read<std::int32_t>();

			if (!test_register) {
				ip += offset;
			}

			break;
		}
		case (oc_jump_false - oo_16): {
			const auto offset = ip.read<std::int16_t>();

			if (!test_register) {
				ip += offset;
			}

			break;
		}
		case (oc_jump_false - oo_8): {
			const auto offset = ip.read<std::int8_t>();

			if (!test_register) {
				ip += offset;
			}

			break;
		}
		case (oc_name - ro_32): {
			token->set(stack.tos(),
			           make_key_value_pair(string_pointer(resources.at(ip.read<std::uint32_t>())),
			                               member_pointer(stack.tos())));

			break;
		}
		case (oc_name - ro_16): {
			token->set(stack.tos(),
			           make_key_value_pair(string_pointer(resources.at(ip.read<std::uint16_t>())),
			                               member_pointer(stack.tos())));

			break;
		}
		case (oc_name - ro_8): {
			token->set(stack.tos(), make_key_value_pair(string_pointer(resources.at(ip.read<std::uint8_t>())),
			                                            member_pointer(stack.tos())));

			break;
		}
		case (oc_return_void): {
			return;
		}
		case (oc_invert): {
			test_register = !test_register;

			break;
		}
		case (oc_drop): {
			stack.drop(ip.read<std::uint8_t>());

			break;
		}
		default: BIA_THROW(exception::opcode, "invalid opcode");
		}
	}
}
