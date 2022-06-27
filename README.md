# LWCppDigitalSignalProcessor

LWCppDigitalSignalProcessor contains a simple class (LWDSP) that can perform digital signal
processing algorithms. Right now, the class can only perform the discrete Fourier transform (DFT).


## Installation
To install LWDSP, simply copy and paste [`LWDSP.cpp`](src/LWDSP.cpp) and
[`LWDSP.cpp`](src/LWDSP.cpp) into your project. Then, include LWDSP by using
`#include <path/to/LWDSP.hpp>`.


## Running tests
```shell
git clone https://github.com/leeway64/LWCppDigitalSignalProcessor.git
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./cmake-build
cmake --build ./cmake-build --target LWCppDigitalSignalProcessor_tests
cmake-build/LWCppDigitalSignalProcessor_tests
```


## Third-Party Software
- [CMake](https://cmake.org/) (BSD-3-Clause): Build system generator.
- [Conan](https://conan.io/) (MIT License): Package manager.
- [Catch2](https://github.com/catchorg/Catch2/tree/v2.x) (MIT License): Unit testing framework.
