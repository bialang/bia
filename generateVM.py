NAME = 0
ARGS = 1
CODE = 2

arg_options = {
    "mso": [
        ("tos", "auto& p{} = stack.tos();"),
        ("args", "auto& p{} = stack.arg_at(ip.read<std::uint8_t>());"),
        ("global_16", "auto& p{} = stack.local_at(ip.read<std::uint16_t>());"),
        ("local_16", "auto& p{} = stack.local_at(ip.read<std::uint16_t>());"),
        ("resource_16", "auto& p{} = stack.local_at(ip.read<std::uint16_t>());"),
        ("global_8", "auto& p{} = stack.local_at(ip.read<std::uint8_t>());"),
        ("local_8", "auto& p{} = stack.local_at(ip.read<std::uint8_t>());"),
        ("resource_8", "auto& p{} = stack.local_at(ip.read<std::uint8_t>());")
    ],
    "mdo": [
        ("tos", "auto& p{} = stack.push();"),
        ("global_16", "auto& p{} = stack.local_at(ip.read<std::uint16_t>());"),
        ("local_16", "auto& p{} = stack.local_at(ip.read<std::uint16_t>());"),
        ("global_8", "auto& p{} = stack.local_at(ip.read<std::uint8_t>());"),
        ("local_8", "auto& p{} = stack.local_at(ip.read<std::uint8_t>());")
    ],
    "co": [
        ("int_8", "const auto p{} = ip.read<std::int8_t>();"),
        ("int_32", "const auto p{} = ip.read<std::int32_t>();"),
        ("int_64", "const auto p{} = ip.read<std::int64_t>();"),
        ("double", "const auto p{} = ip.read<double>();")
    ]
}
opcodes = [
    ("oc_instantiate", ("mdo", "co"), "token.set({0}, creator::create({1}).to<gc::object::base>());"),
	("oc_invoke", ("mdo", "mso"), """const auto parameter_count = ip.read<std::uint8_t>();
token.set({0}, member_pointer({1})->invoke(stack, parameter_count).to<gc::object::base>());
stack.pop(parameter_count);"""),

    ("oc_refer", ("mdo", "mso"), "token.set({0}, {1});"),

	("oc_invoke_void", ("mso",), """const auto parameter_count = ip.read<std::uint8_t>();
member_pointer({0})->invoke(stack, parameter_count);
stack.pop(parameter_count);"""),
	("oc_test", ("mso",), "test_register = member_pointer({0})->test();"),

    ("oc_return_void", tuple(), "return;")
]

for opcode in opcodes:
    args_template = ""

    for i, arg in enumerate(opcode[ARGS]):
        count = ""
        try:
            count = " * {}_count".format(opcode[ARGS][i+1])
        except:
            pass
        args_template += " - {}_{{}}{}".format(arg, count)

    def rec(rest, *args):
        if len(rest) > 0:
            for i in reversed(arg_options[rest[0]]):
                rec(rest[1:], *args, i)
        else:
            print("case ({}{}): {{".format(
                opcode[NAME], args_template.format(*(i[0] for i in args))))
            for index, i in enumerate(args):
                print(i[1].format(index))
            print(opcode[CODE].format(*("p{}".format(i) for i in range(len(args)))))
            print("break;\n}")

    rec(opcode[ARGS])
    #case = "case ({}{}):".format(opcode[NAME], args_template.format([i() for i in args]))

print("default: throw;")