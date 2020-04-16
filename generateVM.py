NAME = 0
ARGS = 1
CODE = 2

arg_options = {
    "mso": [
        ("tos", "stack.tos()"),
        ("args", "stack.arg_at(ip.read<std::uint8_t>())"),
        ("global_16", "stack.local_at(ip.read<std::uint16_t>())"),
        ("local_16", "stack.local_at(ip.read<std::uint16_t>())"),
        ("resource_16", "resources.at(ip.read<std::uint16_t>())"),
        ("global_8", "stack.local_at(ip.read<std::uint8_t>())"),
        ("local_8", "stack.local_at(ip.read<std::uint8_t>())"),
        ("resource_8", "resources.at(ip.read<std::uint8_t>())")
    ],
    "mdo": [
        ("tos", "stack.push()"),
        ("global_16", "stack.local_at(ip.read<std::uint16_t>())"),
        ("local_16", "stack.local_at(ip.read<std::uint16_t>())"),
        ("global_8", "stack.local_at(ip.read<std::uint8_t>())"),
        ("local_8", "stack.local_at(ip.read<std::uint8_t>())")
    ],
    "co": [
        ("int_8", "ip.read<std::int8_t>()"),
        ("int_32", "ip.read<std::int32_t>()"),
        ("int_64", "ip.read<std::int64_t>()"),
        ("double", "ip.read<double>()")
    ]
}
opcodes = [
    ("oc_instantiate", ("co", "mdo"), """const auto constant = {0};

token->set({1}, creator::create(constant).to<bia::member::member>());

break;"""),

    ("oc_invoke", ("mso", "mdo"), """const auto parameter_count = ip.read<std::uint8_t>();
auto result = member_pointer({0})->invoke(stack.frame(parameter_count), parameter_count);

stack.drop(parameter_count);
token->set({1}, std::move(result));

break;"""),


    ("oc_refer", ("mso", "mdo"), """auto& src = {0};

token->set({1}, src);

break;"""),

    ("oc_clone", ("mso", "mdo"), """const auto src = member_pointer({0});

if (src->flags() & flag::flag_clone_is_copy) {{
    token->set({1}, src->copy());
}} else {{
    token->set({1}, src);
}}

break;"""),

    ("oc_copy", ("mso", "mdo"),  """const auto src = member_pointer({0});

token->set({1}, src->copy());

break;"""),


    ("oc_invoke_void", ("mso",), """const auto parameter_count = ip.read<std::uint8_t>();

member_pointer({0})->invoke(stack.frame(parameter_count), parameter_count);
stack.drop(parameter_count);

break;"""),

    ("oc_test", ("mso",), "test_register = member_pointer({0})->test();"),

    ("oc_return_void", tuple(), "return;"),
    ("oc_test_top", tuple(), "test_register = member_pointer(stack.pop())->test();")
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
            print(opcode[CODE].format(*(i[1] for i in args)), end="\n}\n")

    rec(opcode[ARGS])
    #case = "case ({}{}):".format(opcode[NAME], args_template.format([i() for i in args]))

print("default: throw;")
