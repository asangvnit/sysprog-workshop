# What is cmake

[CMake](https://cmake.org/) is a an extremely popular way for building C++ code. It’s a powerful, comprehensive solution for managing the software build process. There are many other alternatives like `Makefiles`, `Visual Studio` legacy build system etc. and many other proprietary ones. But `cmake` shines as it is easy to learn, cross-platform and highly customizable. To get started, you need to create `CMakeLists.txt` file (in the same directory as your test pogram `test.cpp`) as follows:
```cmake
cmake_minimum_required(VERSION 3.11)
project(test)
add_executable(test test.cpp)
```

# How to use cmake?

In the current directory, run:

```sh
$ ls
CMakeLists.txt  test.cpp
$ cmake -S . -B build
-- The C compiler identification is AppleClang 17.0.0.17000319
-- The CXX compiler identification is AppleClang 17.0.0.17000319
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.9s)
-- Generating done (0.0s)
-- Build files have been written to: /home/asangdani/sysprog-workshop/cmakedemo/simple/build

$ ls -l build
total 56
-rw-r--r--@  1 asangdani  staff   2025 Oct 27 14:18 cmake_install.cmake
-rw-r--r--@  1 asangdani  staff  13974 Oct 27 14:18 CMakeCache.txt
drwxr-xr-x@ 14 asangdani  staff    448 Oct 27 14:18 CMakeFiles/
-rw-r--r--@  1 asangdani  staff   5225 Oct 27 14:18 Makefile

$ cmake --build build
[ 50%] Building CXX object CMakeFiles/test.dir/test.cpp.o
[100%] Linking CXX executable test
[100%] Built target test

$ ls -l build/test
-rwxr-xr-x@ 1 asangdani  staff  38824 Oct 27 14:20 build/test*

$ ./build/test
Hello World Works
```

To run the tests, run:

```sh
cd build && ctest -V --output-on-failure
```

Alternatively, you can run:

```sh
cmake --build build --target test
```

To clean the build artifacts, run:

```sh
cmake --build build --target clean
```
