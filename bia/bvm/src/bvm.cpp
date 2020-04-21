#include "bvm/bvm.hpp"

#include "bvm/instruction_pointer.hpp"

#include <bytecode/op_code.hpp>
#include <connector/connector-inl.hpp>
#include <creator/creator.hpp>
#include <exception/nullpointer.hpp>
#include <gc/gcable.hpp>
#include <gc/stack_view.hpp>
#include <gc/token.hpp>
#include <member/member.hpp>
#include <type_traits>
#include <util/finally.hpp>

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

bia::member::member* member_pointer(bia::member::member* element)
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

void bvm::execute(context& context, util::span<const util::byte> instructions, gc::root& resources)
{
	using namespace bytecode;
	using flag = bia::member::member::flag;
	instruction_pointer ip{ instructions.begin(), instructions.end() };
	bia::member::member::test_type test_register{ 10 };
	auto& gc      = context.gc();
	auto& globals = context.symbols();
	auto token    = gc.register_thread(64);
	auto stack    = token->stack_view();

	while (ip) {
		const auto op_code = ip.next_op_code();

		switch (op_code) {
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
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_8 * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_local_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_8 * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_local_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_8 * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_local_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_resource_16 * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(resources.at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_local_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_local_16 * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.local_at(ip.read<std::uint16_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_local_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_global_16 * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_local_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_args * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result                = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))
			                  ->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_local_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(stack.tos())->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_global_8): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(stack.tos())->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint8_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_local_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(stack.tos())->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_global_16): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(stack.tos())->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.local_at(ip.read<std::uint16_t>()), std::move(result));
			}

			break;
		}
		case (oc_invoke - mso_tos * mdo_count - mdo_tos): {
			const auto parameter_count = ip.read<std::uint8_t>();
			auto result = member_pointer(stack.tos())->invoke(stack.frame(parameter_count), parameter_count);

			stack.drop(parameter_count);

			if (result.valid()) {
				token->set(stack.push(), std::move(result));
			}

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
		case (oc_test - mso_resource_8): {
			test_register = member_pointer(resources.at(ip.read<std::uint8_t>()))->test();

			break;
		}
		case (oc_test - mso_local_8): {
			test_register = member_pointer(stack.local_at(ip.read<std::uint8_t>()))->test();

			break;
		}
		case (oc_test - mso_global_8): {
			test_register =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint8_t>()))))->test();

			break;
		}
		case (oc_test - mso_resource_16): {
			test_register = member_pointer(resources.at(ip.read<std::uint16_t>()))->test();

			break;
		}
		case (oc_test - mso_local_16): {
			test_register = member_pointer(stack.local_at(ip.read<std::uint16_t>()))->test();

			break;
		}
		case (oc_test - mso_global_16): {
			test_register =
			    member_pointer(globals.get(*string_pointer(resources.at(ip.read<std::uint16_t>()))))->test();

			break;
		}
		case (oc_test - mso_args): {
			test_register = member_pointer(stack.arg_at(ip.read<std::uint8_t>()))->test();

			break;
		}
		case (oc_test - mso_tos): {
			test_register = member_pointer(stack.tos())->test();

			break;
		}
		case (oc_return_void): {
			return;
		}
		case (oc_drop): {
			stack.drop(ip.read<std::uint8_t>());

			break;
		}
		default: throw;
		}
	}
}
