# Bia
Embedded C++ Scripting Language

# Supported platforms
Currently the x86 architecture with the MSVC compiler is supported. Additional support for x64, ARM, GCC and Clang is planned.

# Embedded example
Bia is still in development thus this example may not be final.
```
//Create context with default settings
std::shared_ptr<bia::machine::BiaAllocator> pAllocator(new bia::machine::BiaAllocator());
bia::machine::BiaMachineContext context(pAllocator);

//Bia script
std::string stTestCode = R"(

print "Hello, World! - Bia";

)";

//Run
context.Run(stTestCode.c_str(), stTestCode.length());
```

# Language features
**Variable Declaration:**
- Global variables `global`: `global i = 0;`

  Global variables can be access by any script in the same context at any time.
- Instantiation: `global obj = new MyClass();`
***
**Function Calls**
- Normal function call: `normal_function();`
- Member function call: `object.function();`
- Optimized member function call. This is more efficient in loops:
```
global function_pointer = object.function;
object->function();
```
***
**Loops**
- While loop:
```
while (true) {
  print "hi";
}
```
- Until loop. These loops are just like `while` loops but with negated condition:
```
until (false) {
  print "hi";
}
```
***
**Conditional statements**
- If statements. Conditions that can be evaluated at compile time will be optimized away:
```
if (true) {
  print true;
}
else if (some_value == 3) {
  print false;
}
```
