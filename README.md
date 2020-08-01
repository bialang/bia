# Bia

![C/C++ CI](https://github.com/bialang/bia/workflows/C/C++%20CI/badge.svg?branch=master)

Embeddable C++11 Scripting Language

:construction: This project is premature and not ready for production user :construction:

The roadmap for this project can be found on [Trello](https://trello.com/b/PFVmLl37).

- [Embedded Example](#embedded-example)
- [Building](#building)
  - [Prerequisites](#prerequisites)
  - [Dependencies](#dependencies)
  - [Compilation](#compilation)
- [License](#license)

## Embedded Example

``` cpp
// create a simple engine with the default settings and allocator
bia::engine engine;

// register a function and the io module
engine.function("hello_world", +[] { std::cout << "Hello, World - C++\n"; });
engine.module<bia::bsl::io>("io", engine.gc());

// bia script
std::stringstream code;

code << u8R"(
  // prints 'Hello, World' to the console
  import io
  io.print("Hello, World! - Bia")

  // calls the C++ function and print 'Hello, World - C++' to the console
  hello_world()
)";

// execute
engine.execute(code);
```

And the corresponding CMake:

```cmake
find_package(bia REQUIRED)
add_executable(example example.cpp)
target_link_libraries(example PRIVATE bia::bia)
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
git clone https://github.com/bialang/bia.git
mkdir bia/build
cd bia/build

cmake ..
cmake --build .

ctest

cmake --build . --target install
```

## License

Bia is distributed under the BSD-3-Clause.
