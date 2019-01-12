# Bia
Embedded C++14 Scripting Language

# Embedded Example

``` cpp
// Create a context with the default memory allocators
bia::machine::machine_context _context;

// Add a lambda function
bia::set_lambda(_context, "hello_world", [] {
  puts("Hello, World! - C++");
});

// Bia script
std::string _code = u8R"(
  # Print 'Hello, World' to the console
  print "Hello, World! - Bia"
  print u8"Hallo, schöne Welt! - German"

  # Call the C++ function and print 'Hello, World' to the console
  hello_world()
)";

// Execute
_context.execute(_code.c_str(), _code.length());
```

# Language Features
## Native types
- Integrals with arbitrary length (uses [MPIR](http://mpir.org/))
- 64-Bit floating point numbers
- Classic C-style string with C++11 string literal support

## Variable Declaration
- Global variables `global`: `global i = 0`

  Global variables can be access by any script in the same context at any time.
- Instantiation: `global obj = my_class()`
- The types of the variables will be deducted from the value
- Once a variable has a tpye it cannot be changed, unless it is redeclared:

```
# var is now a string
global _var = "hello"

# this is invalid
_var = 34

# redeclare as an integral
global _var = 0

# this is now valid
_var = 34
```

## Function Calls
- Normal function call: `normal_function()`
- Member function call: `_object.function()`
- Optimized member function call. This is more efficient in loops:

```
global function_pointer = _object.function
function_pointer()
```

## Loops
### `while` loop

```
while true {
  print "hi"
}
```

### `do while` loop

```
do while true {
  print "hi"
}
```

### `until` loop

These loops are just like `while` loops but with negated condition:

```
until false {
  print "hi"
}
```

### `do until` loop

```
do until false {
  print "hi"
}
```

## Conditional Statements
### `if`, `else if` and `else` statements

Conditions that can be evaluated at compile time will be optimized away:

```
if 1 == 0 {
  print true
} else if _some_value == 3 {
  print false
}
```

# The Simple C++ Interface
## Adding a static function to your context

``` cpp
// A static C++ function
int square(int _base)
{
  return _base * _base;
}

// Adding the function
bia::set_function(_context, "square", &square);
```

## Adding a lambda function

``` cpp
// Adding the function
bia::set_lambda(_context, "int_sqrt", [] (double _value) {
  return static_cast<int>(sqrt(_value));
});
```

 ## Adding a C++ class

``` cpp
// A C++ class
class my_class
{
public:
  my_class(int _value)
  {
    printf("your value: %i\n", _value);
  }
  void print_me()
  {
    puts("hi i'm printing to the screen");
  }
};

// Adding the class
bia::set_class<my_class>(_context, "my_class")
  .set_constructor<int>()
  .set_function("print_me", &my_class::print_me);
```

# How It Works
Bia compiles the script directly to memory before the first run and executes it as a normal C++ function. This technique allows very fast run times since the code is directly executed on the CPU.

# Supported Platforms
Currently the MSVC, GNU (>=4.9) and Clang (>=3.9) compiler on the x86 (32 and 64 Bit) architecture are supported. Additional support for the ARM architecture is planned.

# License
Bia is distributed under the BSD-3-Clause.
