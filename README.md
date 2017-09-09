# Bia
Embedded scripting language for C++

# Embedding example

```
//Initialize bia; only needed once
bia::Bia::Initialize();

//Create context with default settings
bia::machine::BiaMachineContext context;

context.SetFunction("HelloWorld", [] { puts("Hello, World! - C++"); });

//Bia script
auto testCode = u8R"(

print "Hello, World! - Bia";
HelloWorld();

)";

//Compile script
bia::stream::BiaStreamBuffer compiled;
bia::Bia::Compile(testCode, std::char_traits<char>::length(testCode), compiled);

//Print binary output (optional)
bia::machine::debug::BiaDisassembler::DisassembleByteCode(compiled.GetByteStream());

//Run
context.Execute(compiled.GetByteStream());

//Finalize bia
bia::Bia::Finalize();
```
