import re

ptype = [
    ("OC_RETURN_VOID", "", "goto gt_return;", "", "ret")
]
inttype = [
    ("OC_JUMP", "", "instruction_ptr += {};", "", "jmp"),
    ("OC_JUMP_TRUE", "", "instruction_ptr += test_register ? {} : 0;", "", "jpt"),
    ("OC_JUMP_FALSE", "", "instruction_ptr += test_register ? 0 : {};", "", "jpf")
]
itype = [
]
mtype = [
]
minttype = [
]
mmtype = [
]
mitype = [
]
mminttype = [
]
mmmtype = [
]
mmitype = [
]

mvars = [
    ("MOCO_TINY_TEMPORARY", "auto {0} = _temps[read<tiny_member_index_t>(_cursor)];"),
    ("MOCO_TINY_PERMANENT", "auto {0} = _globals[read<tiny_member_index_t>(_cursor)];"),
    ("MOCO_TEMPORARY", "auto {0} = _temps[read<member_index_t>(_cursor)];"),
    ("MOCO_PERMANENT", "auto {0} = _globals[read<member_index_t>(_cursor)];")
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
    ("IOCO_STRING", "auto _immediate = _string_manager.string<char>(read<string_manager::index_t>(_cursor));")
]
o = open("vmcode.generated", "w")
d = open("dissassembler.generated", "w")

def write(x):
    o.write(x)
    d.write(x)

def format_var_decl(var):
    if "_string_manager" in var:
        return var
    return re.match(r"^auto \w+ = ", var)[0] + re.search(r"read<\w+>\(_cursor\)", var)[0] + ";"

def name_of_var(var):
    tmp = re.search(r"auto(?:\s|&)*(\w+) = (.*?)read<", var)
    
    if tmp[1] == "_immediate" or tmp[1] == "_int":
        return 'i", ' + tmp[1]
    elif tmp[2] == "_globals[":
        return 'm", ' + tmp[1]
    elif tmp[2] == "_temps.from_front(":
        return 't", ' + tmp[1]
    elif tmp[2] == "_temps.from_back(":
        return 'l", ' + tmp[1]
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


write("switch (instruction_ptr.next_op_code()) {\n/** P-Type */\n\t\t")

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

write("/** Mint-Type */\n\t\t")

# Write Mint-Type
for i in minttype:
    for v0 in mvars:
        for v1 in intvars:
            write_case(*i, xoffset=v1[0], yoffset=v0[0], xmax="IIOCO_COUNT", var0=v0[1].format("_member"), var1=v1[1])

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

write("/** MMint-Type */\n\t\t")

# Write MMint-Type
for i in mminttype:
    for v0 in mvars:
        for v1 in mvars:
            for v2 in intvars:
                write_case(*i, xoffset=v2[0], yoffset=v1[0], zoffset=v0[0], xmax="IIOCO_COUNT", ymax="MOCO_COUNT", var0=v0[1].format("_member0"), var1=v1[1].format("_member1"), var2=v2[1])

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
write('default:\nthrow exception::invalid_op_code_error(u"invalid op code");\n}')

o.close()
d.close()