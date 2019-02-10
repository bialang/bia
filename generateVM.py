
ptype = [
    ("OC_RETURN", "goto gt_return;")
]
inttype = [
    ("OC_SETUP", ""),
    ("OC_JUMP", "_cursor += _int;"),
    ("OC_JUMP_TRUE", "_cursor += _test_register ? _int : 0;"),
    ("OC_JUMP_FALSE", "_cursor += _test_register ? 0 : _int;")
]
itype = [
    ("OC_PUSH_IMMEDIATE", "_stack.push(_immediate);")
]
mtype = [
    ("OC_TEST", "_test_register = _member->test();"),
    ("OC_PUSH", "_stack.push(_member);"),
    ("OC_EXECUTE_VOID", "_member->execute(nullptr);"),
    ("OC_UNDEFINE", "_member->undefine();")
]
mmtype = [
    ("OC_EXECUTE", "_member0->execute(_member1);"),
    ("OC_CLONE", "_member0->clone(_member1);"),
    ("OC_REFER", "_member0->refer(_member1);"),
    ("OC_COPY", "_member0->copy(_member1);")
]
mitype = [
    ("OC_INSTANTIATE", "framework::create_member(_member, _immediate);")
]

mvars = [
    ("MOCO_TINY_MEMBER", "auto {0} = _globals[read<tiny_member_index_t>(_cursor)];"),
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
    ("IOCO_FLOAT", "auto _immediate = read<double>(_cursor);")
]
o = open("out.txt", "w")

def write_case(op_code, code, xoffset=None, xmax=None, yoffset=None, var0=None, var1=None):
    if xoffset is None:
        offset = ""
    else:
        if xmax is None or yoffset is None:
            offset = " - " + xoffset
        else:
            offset = " - ({0} * {1} + {2})".format(yoffset, xmax, xoffset)
    
    o.write("case ({op_code}{offset}):\n\t\t{{\n\t\t\t{var0}{var1}{code}\n\t\t\tbreak;\n\t\t}}\n\t\t".format(
        op_code=op_code,
        offset=offset,
        var0=var0 + "\n\t\t\t" if var0 is not None else "",
        var1=var1 + "\n\t\t\t" if var1 is not None else "",
        code=code
    ))


o.write("switch (_operation) {\n\t\t/** P-Type */\n\t\t")

# Write P-Type
for i in ptype:
    write_case(*i)

o.write("/** int-Type */\n\t\t")

# Write int-Type
for i in inttype:
    for v in intvars:
        write_case(*i, xoffset=v[0], var0=v[1])

o.write("/** I-Type */\n\t\t")

# Write I-Type
for i in itype:
    for v in ivars:
        write_case(*i, xoffset=v[0], var0=v[1])

o.write("/** M-Type */\n\t\t")

# Write M-Type
for i in mtype:
    for v in mvars:
        write_case(*i, xoffset=v[0], var0=v[1].format("_member"))

o.write("/** MM-Type */\n\t\t")

# Write MM-Type
for i in mmtype:
    for v0 in mvars:
        for v1 in mvars:
            write_case(*i, xoffset=v1[0], yoffset=v0[0], xmax="MOCO_COUNT", var0=v0[1].format("_member0"), var1=v1[1].format("_member1"))

o.write("/** MI-Type */\n\t\t")

# Write MI-Type
for i in mitype:
    for v0 in mvars:
        for v1 in ivars:
            write_case(*i, xoffset=v1[0], yoffset=v0[0], xmax="IOCO_COUNT", var0=v0[1].format("_member"), var1=v1[1])

# Finalize
o.write("default:\n\t\t\tBIA_IMPLEMENTATION_ERROR;\n\t\t}")
o.close()