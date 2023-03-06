# LWCppDigitalSignalProcessor


[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/leeway64/LWCppDigitalSignalProcessor)


LWCppDigitalSignalProcessor contains a class (`LWDSP`) that can perform digital signal
processing algorithms. Right now, the class can only perform the
[discrete Fourier transform (DFT)](https://en.wikipedia.org/wiki/Discrete_Fourier_transform).


## Installation

To install LWCppDigitalSignalProcessor you can clone this entire repository:
```bash
git clone https://github.com/leeway64/LWCppDigitalSignalProcessor.git
```

Or you can simply include [`LWDSP.hpp`](src/LWDSP.hpp).


## Running Unit Tests
```bash
git clone https://github.com/leeway64/LWCppDigitalSignalProcessor.git
cd LWCppDigitalSignalProcessor
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./cmake-build
cmake --build ./cmake-build --target LWCppDigitalSignalProcessor_tests
cmake-build/LWCppDigitalSignalProcessor_tests
```


## Third-Party Software
- [CMake](https://cmake.org/) (BSD-3-Clause): Build system generator.
- [Conan](https://conan.io/) (MIT License): Package manager.
- [Catch2](https://github.com/catchorg/Catch2/tree/v2.x) (MIT License): Unit testing framework.
