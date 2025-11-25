## Requirments:
* C++20
* CMake 3.15+
* Visual Studio 17 2022 or newer

## Getting started:
##### 1. Clone this repo:
```
git clone https://github.com/UnevenBird/limb.git --recurse-submodules limb
cd limb
```

##### 2. Generate project:
```
mkdir build
cd build
cmake .. -G "Visual Studio 18 2026" -A x64
```
> You can choose a different version of Visual Studio, just replace "Visual Studio 18 2026" with some other from the list:
https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators

##### 3. Build
```
cmake --build . --config Release
```