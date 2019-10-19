import re

ptype = [("OC_RETURN_VOID", "return;", "ret")]
inttype = [("OC_JUMP", "instruction_ptr += {};", "jmp"),
	("OC_JUMP_TRUE", "instruction_ptr += test_register ? {} : 0;", "jpt"),
	("OC_JUMP_FALSE", "instruction_ptr += test_register ? 0 : {};", "jpf"),
	("OC_POP", "stack.pop({});", "pop")]
itype = [("OC_PUSH_IMMEDIATE", 'stack.push({});', "push"),
	("OC_RETURN_IMMEDIATE", "", "ret")]
mtype = [("OC_PUSH_MEMBER", "", "push"),
	("OC_RETURN_MEMBER", "", "ret"),
	("OC_TEST", "test_register = static_cast<bool>({}.get<member::member>()->test());", "test")]
mmintinttype = [("OC_CALL", "gc_token.set({0}, {1}.get<member::member>()->call(&stack, {2}));\nstack.pop({3});", "call")]

mvars = [("MOCO_TEMP", "auto& {} = gc_token.root_at(0)[instruction_ptr.read<std::uint32_t>()];"),
	("MOCO_TINY_TEMP", "auto& {} = gc_token.root_at(0)[instruction_ptr.read<std::uint8_t>()];"),]
intvars = [("IIOCO_INT32", "auto {} = instruction_ptr.read<std::int32_t>();"),
	("IIOCO_INT8", "auto {} = instruction_ptr.read<std::int8_t>();")]
ivars = [("IOCO_STRING", "auto {} = \"some placeholder\";"),
	("IOCO_TEST_REGISTER", "auto {} = test_register;"),
	("IOCO_FLOAT", "auto {} = instruction_ptr.read</*placeholder*/std::int64_t>();"),
	("IOCO_INT64", "auto {} = instruction_ptr.read<std::int64_t>();"),
	("IOCO_INT32", "auto {} = instruction_ptr.read<std::int32_t>();"),
	("IOCO_INT8", "auto {} = instruction_ptr.read<std::int8_t>();")]

o = open("vmcode.generated", "w")
d = open("dissassembler.generated", "w")

def write(x):
	o.write(x)
	d.write(x)

def get_max(var):
	return re.sub(r"^([^_]+_).*", "\\g<1>COUNT", var)

def case_unravel(*args):
	if len(args) > 1:
		return "({} * {} + {})".format(case_unravel(*args[1:]), get_max(args[0][0]), args[0][0])
	return args[0][0]

def make_case(op_code, *args):
	if len(args) > 0:
		return "({} - {})".format(op_code, case_unravel(*args))
	return op_code

def write_case(op_code, vmcode, name, *args):
	names = []
	code = ""
	for i, v in enumerate(args):
		names.append("p{}".format(i))
		code += v[1].format(names[i]) + "\n"

	code += vmcode if vmcode == "return;" else vmcode.format(*names) + "\nbreak;"

	write("case {case}: {{\n{code}\n}}".format(case=make_case(op_code, *args[::-1]), code=code))


write("switch (instruction_ptr.next_op_code()) {\n/** P-Type */\n")

# Write P-Type
for i in ptype:
	write_case(*i)

write("\n/** int-Type */\n")

# Write int-Type
for i in inttype:
	for v in intvars:
		write_case(*i, v)

write("\n/** I-Type */\n")

# Write I-Type
for i in itype:
	for v in ivars:
		write_case(*i, v)

write("\n/** M-Type */\n")

# Write M-Type
for i in mtype:
	for v in mvars:
		write_case(*i, v)
		
write("\n/** MMintint-Type */\n")

# Write mmintint-Type
for i in mmintinttype:
	for y in mvars:
		for e in mvars:
			for v in intvars:
				for x in intvars:
					write_case(*i, y, e, v, x)

# Finalize
write('default:\nBIA_THROW(exception::invalid_op_code_exception, u"invalid op code");\n}')

o.close()
d.close()