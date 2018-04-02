# Bia
Embedded C++ Scripting Language

[![Build status](https://ci.appveyor.com/api/projects/status/hgg15mmsrffx3dua/branch/master?svg=true)](https://ci.appveyor.com/project/terrakuh/bia/branch/master)

# Embedded Example

```
//Create a context with the default memory allocator
std::shared_ptr<bia::machine::BiaAllocator> pAllocator(new bia::machine::BiaAllocator());
bia::machine::BiaMachineContext context(pAllocator);

//Add a lambda function
context.SetLambda("hello_world", [] {
  puts("Hello, World! - C++");
});

//Bia script
std::string stTestCode = R"(

# Print 'Hello, World' to the console
print "Hello, World! - Bia"

# Call the C++ function and print 'Hello, World' to the console
hello_world()

)";

//Execute
context.Execute(stTestCode.c_str(), stTestCode.length());
```

# Language Features
**Native types**
- Integrals with a range from -2^32 to 2^32-1
- 32- and 64-Bit floating points
- Zero terminated strings

**Variable Declaration:**
- Global variables `global`: `global i = 0`

  Global variables can be access by any script in the same context at any time.
- Instantiation: `global obj = new MyClass()`
- The types of the variables will be deducted from the value
- Once a variable has a tpye it cannot be changed, unless it is redeclared:

```
# var is now a string
global var = "hello"

# this is invalid
var = 34

# redeclare as an integral
global var = 0

# this is now valid
var = 34
```

**Function Calls**
- Normal function call: `normal_function()`
- Member function call: `object.function()`
- Optimized member function call. This is more efficient in loops:

```
global function_pointer = object.function
object->function_pointer()
```

**Loops**
- While loop:

```
while true {
  print "hi"
}
```

- Do-While loop:

```
do while true {
  print "hi"
}
```

- Until loop. These loops are just like `while` loops but with negated condition:

```
until false {
  print "hi"
}
```

- Do-Until loop.

```
do until false {
  print "hi"
}
```

**Conditional Statements**
- If statements. Conditions that can be evaluated at compile time will be optimized away:

```
if 1 == 0 {
  print true
}
else if some_value == 3 {
  print false
}
```

# The Simple C++ Interface
- Adding a static function to your `context`:

```
//A static C++ function
int square(int base)
{
  return a * a;
}

//Adding the function
context.SetFunction("square", &square);
```

- Adding a lambda function:

```
//Adding the function
context.SetLambda("int_sqrt", [] (double v) {
  return static_cast<int>(sqrt(v));
});
```

- Adding a C++ class:

```
//A C++ class
class MyClass
{
public:
  MyClass(int someValue)
  {
    printf("your value: %i\n", someValue);
  }
};

//Adding the class
context.SetTemplate<MyClass>("my_class")->SetConstructor<int>();
```

# How It Works
Bia compiles the script directly to memory before the first run and executes it as a normal C++ function. This technique allows very fast run times since the code is directly executed on the CPU.

# Supported Platforms
Currently the x86 architecture with the MSVC compiler is supported. Additional support for x64, ARM, GCC and Clang is planned.
