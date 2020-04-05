project(compiler
	LANGUAGES CXX)
	
create_library(STATIC
	PUBLIC bytecode
	PUBLIC tokenizer)