# Bia
Embedded C++ Scripting Language

# Supported platforms
Currently the x86 architecture with the MSVC compiler is supported.
Additional support for x64, ARM, GCC and Clang is planned.

# Embedded example
Bia is still in development thus this example may not be final.
```
//Create context with default settings
std::shared_ptr<bia::machine::BiaAllocator> pAllocator(new bia::machine::BiaAllocator());
bia::machine::BiaMachineContext context(pAllocator);

//Bia script
auto testCode = u8R"(

print "Hello, World! - Bia";

)";

//Compile script
bia::stream::BiaStreamBuffer compiled;
bia::Bia::Compile(testCode, std::char_traits<char>::length(testCode), compiled);

//Print binary output (optional)
bia::machine::debug::BiaDisassembler::DisassembleByteCode(compiled.GetByteStream());

//Run
context.Run(testCode, sizeof(testCode) - 1);
```
