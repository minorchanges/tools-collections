# qt-threadmod
QT project that shows how an external thread can modify a QT Widget via signals/slots in a thread-safe way

## Build with pure CMake:

`cmake -B build` <br>
`cmake --build build`

## Conan:

`conan install . --output-folder=build --build=missing`

to initialize conan and make it fetch all needed libraries. Then run

`cmake -B build --preset conan-default` <br>
`cmake --build --preset conan-release`

to configure and build the project.

To also have a debug configuration, use

`conan install . --output-folder=build --build=missing --settings=build_type=Debug`

and build with

`cmake --build --preset conan-debug`

