# Simple but Essential Library (SEL)

## Description

SEL is a simple header-only C++ library that aims to help developers by providing multiple classes and functions which are often useful for a lot of projects.


## Features

The library features:
* Math classes including random number generation, vectors and matrices.
* Classes to help developers with threads.
* Many other utility classes and functions.


## How to use

First, clone the repository.

```shell
git clone https://github.com/ClementDrn/SEL
```

Then, set the `include` directory as an include directory in your project.

And that is it, easy, right? 

You can now use the library by including `SEL/sel.hpp` or a more specific file like `SEL/Maths/Random.hpp`.

```cpp
// Example of include
#include <SEL/Maths/Random.hpp>
```


## Tests

Requires a C++17 compiler, CMake 3.21+, Python 3.6+, Git, and a build tool;
CMake downloads Catch2 on the first run.

Configure, build, and run tests with the following commands:
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --parallel
ctest --test-dir build -C Debug --output-on-failure
```


## License

This library is licensed under the [MIT](./LICENSE) license.
