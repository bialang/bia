# Bia

Embeddable C++11 Scripting Language

- [Embedded Example](#embedded-example)
- [Building](#building)
	- [Prerequisites](#prerequisites)
	- [Dependencies](#dependencies)
	- [Compilation](#compilation)
- [License](#license)

## Embedded Example

``` cpp
// create a simple engine with the default settings and allocator
bia::engine eng;

// register a lambda
eng.lambda("hello_world", [] {
  std::cout << "Hello, World - C++\n";
});

// bia script
std::string code = u8R"(
  // prints 'Hello, World' to the console
  import io
  io.print("Hello, World! - Bia")

  // calls the C++ function and print 'Hello, World - C++' to the console
  hello_world()
)";

// execute
eng.execute({ code.c_str(), code.length() });
```

## Building

### Prerequisites

- **CMake** *>=3.1*
- C++11 compatible compiler
- Git for cloning

### Dependencies

Bia can be built without any third-party dependencies! However, some are recommended for performance gains and more features:

- **Catch2** for testing *(if not provided, no tests will be build)*

### Compilation

```sh
git clone https://github.com/terrakuh/Bia.git
mkdir Bia/build
cd Bia/build

cmake ..
cmake --build .

ctest

cmake --build . --target install
```

## License

Bia is distributed under the BSD-3-Clause.
