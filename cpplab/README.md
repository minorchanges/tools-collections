# minimalexample
Most basic template. Start here.

# Build

### Pure cmake
cmake -B build
cmake --build build

### Conan
conan install . --output-folder=build --build=missing --settings=build_type=Debug
conan --preset conan-default
conan --build --preset conan-debug

