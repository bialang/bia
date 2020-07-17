#include <bia/bytecode/op_code.hpp>
#include <bia/bytecode/writer/variation.hpp>
#include <bitset>
#include <catch.hpp>
#include <iostream>

using namespace bia::bytecode;

TEST_CASE("opcodes", "[bytecode]")
{
	REQUIRE(to_op_code_base(oc_operator) == oc_operator);
	REQUIRE(to_op_code_base(oc_get) == oc_get);
	REQUIRE(to_op_code_base(oc_test) == oc_test);
	REQUIRE(to_op_code_base(oc_invoke) == oc_invoke);
	REQUIRE(to_op_code_base(oc_instantiate) == oc_instantiate);
	REQUIRE(to_op_code_base(oc_refer) == oc_refer);
	REQUIRE(to_op_code_base(oc_clone) == oc_clone);
	REQUIRE(to_op_code_base(oc_copy) == oc_copy);
	REQUIRE(to_op_code_base(oc_self_operator) == oc_self_operator);
	REQUIRE(to_op_code_base(oc_import) == oc_import);
	REQUIRE(to_op_code_base(oc_jump) == oc_jump);
	REQUIRE(to_op_code_base(oc_jump_true) == oc_jump_true);
	REQUIRE(to_op_code_base(oc_jump_false) == oc_jump_false);
	REQUIRE(to_op_code_base(oc_name) == oc_name);
	REQUIRE(to_op_code_base(oc_return_void) == oc_return_void);
	REQUIRE(to_op_code_base(oc_invert) == oc_invert);
	REQUIRE(to_op_code_base(oc_drop) == oc_drop);
}

template<op_code OpCode, typename... Variations>
inline bool check_variations(Variations... variations)
{
	return parse_options<OpCode, Variations...>(writer::encode_variations<OpCode>(variations...)) ==
	       std::make_tuple(variations...);
}

TEST_CASE("opcode variations", "[bytecode]")
{
	REQUIRE(check_variations<oc_operator>(mso_local_16, mso_resource_16, mdo_args_8));
	REQUIRE(check_variations<oc_operator>(mso_global_16, mso_args_16, mdo_local_8));
	REQUIRE(check_variations<oc_operator>(mso_args_16, mso_builtin, mdo_args_16));
	REQUIRE(check_variations<oc_operator>(mso_builtin, mso_builtin, mdo_args_16));
	REQUIRE(check_variations<oc_operator>(mso_builtin, mso_builtin, mdo_local_8));

	REQUIRE(check_variations<oc_get>(mso_local_16, ro_16, mdo_args_8));
	REQUIRE(check_variations<oc_get>(mso_global_16, ro_16, mdo_local_8));
	REQUIRE(check_variations<oc_get>(mso_args_16, ro_32, mdo_args_16));
	REQUIRE(check_variations<oc_get>(mso_builtin, ro_32, mdo_args_16));
	REQUIRE(check_variations<oc_get>(mso_builtin, ro_8, mdo_local_8));

	REQUIRE(check_variations<oc_invoke>(mso_builtin,  mdo_args_16));
	REQUIRE(check_variations<oc_invoke>(mso_builtin,  mdo_local_8));
	REQUIRE(check_variations<oc_invoke>(mso_args_16,  mdo_args_16));
	REQUIRE(check_variations<oc_invoke>(mso_args_16,  mdo_local_8));
}
