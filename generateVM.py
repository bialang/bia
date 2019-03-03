import re

ptype = [
    ("OC_RETURN", "", "goto gt_return;", "", "ret"),
    ("OC_PUSH_TEST", "", "_stack.push(_test_register);", "", "pusht")
]
inttype = [
    ("OC_SETUP", "", "_temps.create(_int);", "", "setup"),
    ("OC_JUMP", "", "_cursor += _int;", "", "jmp"),
    ("OC_JUMP_TRUE", "", "_cursor += _test_register ? _int : 0;", "", "jpt"),
    ("OC_JUMP_FALSE", "", "_cursor += _test_register ? 0 : _int;", "", "jpf")
]
itype = [
    ("OC_PUSH_IMMEDIATE", "", "_stack.push(_immediate);", "", "push")
]
mtype = [
    ("OC_TEST", "", "_test_register = _member->test();", "", "test"),
    ("OC_PUSH", "", "_stack.push(_member);", "", "push"),
    ("OC_UNDEFINE", "", "_member->undefine();", "", "undf"),
    ("OC_EXECUTE_VOID", "", "_member->execute(nullptr);", "", "exec"),
    ("OC_EXECUTE_COUNT_VOID", "auto _count = read<framework::member::parameter_count_t>(_cursor);", "_member->execute_count(nullptr, nullptr, _count, &_stack);", "", "exec"),
    ("OC_EXECUTE_FORMAT_VOID", "auto _count = read<framework::member::parameter_count_t>(_cursor);", 
                                "if (_cursor + _count > _end) {\n\t\t\t\t"
                                    "BIA_IMPLEMENTATION_ERROR;\n\t\t\t"
                                "}\n\t\t\t_member->execute_format(nullptr, reinterpret_cast<const char*>(_cursor), _count, &_stack);", "_cursor += _count;", "exec")
]
mmtype = [
    ("OC_EXECUTE", "", "_member0->execute(_member1);", "", "exec"),
    ("OC_EXECUTE_COUNT", "auto _count = read<framework::member::parameter_count_t>(_cursor);", "_member0->execute_count(_member1, nullptr, _count, &_stack);", "", "exec"),
    ("OC_EXECUTE_FORMAT", "auto _count = read<framework::member::parameter_count_t>(_cursor);",
                            "if (_cursor + _count > _end) {\n\t\t\t\t"
                                "BIA_IMPLEMENTATION_ERROR;\n\t\t\t"
                            "}\n\t\t\t_member0->execute_format(_member1, reinterpret_cast<const char*>(_cursor), _count, &_stack);", "_cursor += _count;", "exec"),
    ("OC_CLONE", "", "_member0->clone(_member1);", "", "cln"),
    ("OC_REFER", "", "_member0->refer(_member1);", "", "ref"),
    ("OC_COPY", "", "_member0->copy(_member1);", "", "cpy"),
    ("OC_TEST_MEMBER", "auto _operator = read<framework::operator_t>(_cursor);", "_test_register = _member0->test_member(_operator, _member1);", "", "test"),
    ("OC_OPERATOR_CALL_VOID", "auto _operator = read<framework::operator_t>(_cursor);", "_member0->operator_call(nullptr, _operator, _member1);", "", "opr")
]
mitype = [
    ("OC_INSTANTIATE", "", "framework::create_member(_member, _immediate);", "", "inst"),
    ("OC_TEST_IMMEDIATE", "auto _operator = read<framework::operator_t>(_cursor);", "_test_register = test(_member, _operator, _immediate);", "", "test"),
    ("OC_TEST_IMMEDIATE_REVERSE", "auto _operator = read<framework::operator_t>(_cursor);", "_test_register = test_reverse(_member, _operator, _immediate);", "", "testr"),
    ("OC_OPERATOR_CALL_IMMEDIATE_VOID", "auto _operator = read<framework::operator_t>(_cursor);", "operator_call(_member, nullptr, _operator, _immediate);", "", "opr"),
    ("OC_OPERATOR_CALL_IMMEDIATE_REVERSE_VOID", "auto _operator = read<framework::operator_t>(_cursor);", "operator_call_reverse(_member, nullptr, _operator, _immediate);", "", "oprr")
]
mmmtype = [
    ("OC_OPERATOR_CALL", "auto _operator = read<framework::operator_t>(_cursor);", "_member0->operator_call(_member1, _operator, _member2);", "", "opr")
]
mmitype = [
    ("OC_OPERATOR_CALL_IMMEDIATE", "auto _operator = read<framework::operator_t>(_cursor);", "operator_call(_member0, _member1, _operator, _immediate);", "", "opr"),
    ("OC_OPERATOR_CALL_IMMEDIATE_REVERSE", "auto _operator = read<framework::operator_t>(_cursor);", "operator_call_reverse(_member0, _member1, _operator, _immediate);", "", "oprr")
]

mvars = [
    ("MOCO_TINY_TEMP", "auto {0} = _temps[read<tiny_member_index_t>(_cursor)];"),
    ("MOCO_TINY_MEMBER", "auto {0} = _globals[read<tiny_member_index_t>(_cursor)];"),
    ("MOCO_TEMP", "auto {0} = _temps[read<member_index_t>(_cursor)];"),
    ("MOCO_MEMBER", "auto {0} = _globals[read<member_index_t>(_cursor)];")
]
intvars = [
    ("IIOCO_INT32", "auto _int = read<int32_t>(_cursor);"),
    ("IIOCO_INT8", "auto _int = read<int8_t>(_cursor);")
]
ivars = [
    ("IOCO_INT32", "auto _immediate = read<int32_t>(_cursor);"),
    ("IOCO_INT8", "auto _immediate = read<int8_t>(_cursor);"),
    ("IOCO_INT64", "auto _immediate = read<int64_t>(_cursor);"),
    ("IOCO_FLOAT", "auto _immediate = read<double>(_cursor);"),
    ("IOCO_STRING", "auto & _immediate = _string_manager.string(read<string_manager::index_t>(_cursor));")
]
o = open("vmcode.generated", "w")
d = open("dissassembler.generated", "w")

def write(x):
    o.write(x)
    d.write(x)

def format_var_decl(var):
    return re.sub(r"((_globals|_temps)\[|])", "", var)

def name_of_var(var):
    tmp = re.search(r"auto(?:\s|&)*(\w+) = (.*?)read<", var)
    
    if tmp[1] == "_immediate" or tmp[1] == "_int":
        return 'i", ' + tmp[1]
    elif tmp[2] == "_globals[":
        return 'm", ' + tmp[1]
    elif tmp[2] == "_temps[":
        return 't", ' + tmp[1]
    else:
        return '", ' + tmp[1]

def write_case(op_code, preparations, code, cleanup, name, xoffset=None, xmax=None, yoffset=None, ymax=None, zoffset=None, var0=None, var1=None, var2=None):
    if xoffset is None:
        offset = ""
    else:
        if xmax is None or yoffset is None:
            offset = " - " + xoffset
        else:
            if zoffset is None or ymax is None:
                offset = " - ({0} * {1} + {2})".format(yoffset, xmax, xoffset)
            else:
                offset = " - (({0} * {1} + {2}) * {3} + {4})".format(zoffset, ymax, yoffset, xmax, xoffset)
    
    tmp = "case ({op_code}{offset}):\n\t\t{{{{\n\t\t\t{{var0}}{{var1}}{{var2}}{prep}{{code}}\n\t\t\t{cleanup}break;\n\t\t}}}}\n\t\t".format(
        op_code=op_code,
        prep=preparations + "\n\t\t\t" if preparations else "",
        cleanup=cleanup + "\n\t\t\t" if cleanup else "",
        offset=offset
    )

    o.write(tmp.format(
        var0=var0 + "\n\t\t\t" if var0 else "",
        var1=var1 + "\n\t\t\t" if var1 else "",
        var2=var2 + "\n\t\t\t" if var2 else "",
        code=code
    ))

    param = "".join(((" " if i == var0 else ', " ') + name_of_var(i) if i else "") for i in [var0, var1, var2, preparations])

    d.write(tmp.format(
        var0=format_var_decl(var0) + "\n\t\t\t" if var0 else "",
        var1=format_var_decl(var1) + "\n\t\t\t" if var1 else "",
        var2=format_var_decl(var2) + "\n\t\t\t" if var2 else "",
        code="print_all(\"{name}{param});".format(name=name, param=param if param else '"')
    ))


write("switch (_operation) {\n\t\t/** P-Type */\n\t\t")

# Write P-Type
for i in ptype:
    write_case(*i)

write("/** int-Type */\n\t\t")

# Write int-Type
for i in inttype:
    for v in intvars:
        write_case(*i, xoffset=v[0], var0=v[1])

write("/** I-Type */\n\t\t")

# Write I-Type
for i in itype:
    for v in ivars:
        write_case(*i, xoffset=v[0], var0=v[1])

write("/** M-Type */\n\t\t")

# Write M-Type
for i in mtype:
    for v in mvars:
        write_case(*i, xoffset=v[0], var0=v[1].format("_member"))

write("/** MM-Type */\n\t\t")

# Write MM-Type
for i in mmtype:
    for v0 in mvars:
        for v1 in mvars:
            write_case(*i, xoffset=v1[0], yoffset=v0[0], xmax="MOCO_COUNT", var0=v0[1].format("_member0"), var1=v1[1].format("_member1"))

write("/** MI-Type */\n\t\t")

# Write MI-Type
for i in mitype:
    for v0 in mvars:
        for v1 in ivars:
            write_case(*i, xoffset=v1[0], yoffset=v0[0], xmax="IOCO_COUNT", var0=v0[1].format("_member"), var1=v1[1])

write("/** MMM-Type */\n\t\t")

# Write MMM-Type
for i in mmmtype:
    for v0 in mvars:
        for v1 in mvars:
            for v2 in mvars:
                write_case(*i, xoffset=v2[0], yoffset=v1[0], zoffset=v0[0], xmax="MOCO_COUNT", ymax="MOCO_COUNT", var0=v0[1].format("_member0"), var1=v1[1].format("_member1"), var2=v2[1].format("_member2"))

write("/** MMI-Type */\n\t\t")

# Write MMI-Type
for i in mmitype:
    for v0 in mvars:
        for v1 in mvars:
            for v2 in ivars:
                write_case(*i, xoffset=v2[0], yoffset=v1[0], zoffset=v0[0], xmax="IOCO_COUNT", ymax="MOCO_COUNT", var0=v0[1].format("_member0"), var1=v1[1].format("_member1"), var2=v2[1])

# Finalize
write("default:\n\t\t\tBIA_IMPLEMENTATION_ERROR;\n\t\t}")

o.close()
d.close()