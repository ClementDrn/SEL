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

And that'it, easy, right?

You can now use the library by including `SEL/sel.hpp` or a more specific file like `SEL/Maths/Random.hpp`.

```cpp
// Example of include
#include <SEL/Maths/Random.hpp>
```


## Example: Int4 Matrix Multiplication

```cpp
#define SEL_INTRINSIC_MATRIX_MUL    // Optional: Enable matrix multiplication optimizations (requires "-msse4.1" g++ flag)
#include <SEL/Maths/Matrix.hpp>
#include <iostream>

int main()
{
    sel::Mat4x4i4 a = {     // Initialize matrix with values
        1, 3, 5, 7,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    a[0][3] += 1;       // 7 + 1 wraps to -8 (due to Int4's format)

    sel::Mat4x4i4 b(2);     // Initialize diagonal matrix with 2s
    auto c = a * b;         // Multiply matrices

    std::cout << c[0][1] << std::endl;      // Prints 6
}
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


## Matrix benchmarks

Compare explicit SIMD on/off in Release mode (x86 with SSE4.1). Compiler
auto-vectorization stays enabled in both builds.
```shell
cmake -S . -B build/benchmarks -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DSEL_BUILD_BENCHMARKS=ON
cmake --build build/benchmarks --target sel_bench_compare --config Release --parallel 2
```


## License

This library is licensed under the [MIT](./LICENSE) license.
