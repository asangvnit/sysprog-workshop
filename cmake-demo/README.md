<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [What is cmake and why use it?](#what-is-cmake-and-why-use-it)
- [Installing cmake](#installing-cmake)
  - [Debian/Ubuntu Linux](#debianubuntu-linux)
  - [MacOS](#macos)
- [How to use cmake?](#how-to-use-cmake)
- [More advanced example](#more-advanced-example)
  - [helloprint.h](#helloprinth)
  - [helloprint.cpp](#helloprintcpp)
  - [cpphello.cpp](#cpphellocpp)
  - [CMakeLists.txt](#cmakeliststxt)
- [Automated testing with googletest](#automated-testing-with-googletest)
  - [hello_test.cpp](#hello_testcpp)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## What is cmake and why use it?

[CMake](https://cmake.org/) is a an extremely popular way for building C++ software. Large software systems need efficient (incremental and customizable) build systems and automated way to test the changes. `cmake` makes it possible to scale a build system and is easy to use. It is powerful and comprehensive solution for managing the software build process. There are many other alternatives like [GNU Makefiles](https://www.gnu.org/software/make/manual/make.html), [Visual Studio](https://code.visualstudio.com/docs/csharp/build-tools) legacy build system etc. and many other proprietary ones. But `cmake` shines as it is easy to learn, cross-platform and highly customizable.

## Installing cmake

On windows [Download cmake binary installer](https://cmake.org/download/), double click the installer file and follow the instructions to completion. On other systems, the installation is straightforward.

### Debian/Ubuntu Linux

```sh
$ sudo apt install -y cmake
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following additional packages will be installed:
  cmake-data libjsoncpp25 librhash0
Suggested packages:
  cmake-doc cmake-format elpa-cmake-mode ninja-build
The following NEW packages will be installed:
  cmake cmake-data libjsoncpp25 librhash0
0 upgraded, 4 newly installed, 0 to remove and 0 not upgraded.
Need to get 13.6 MB of archives.
After this operation, 49.1 MB of additional disk space will be used.
Get:1 http://archive.ubuntu.com/ubuntu noble/main amd64 libjsoncpp25 amd64 1.9.5-6build1 [82.8 kB]
Get:2 http://archive.ubuntu.com/ubuntu noble/main amd64 librhash0 amd64 1.4.3-3build1 [129 kB]
Get:3 http://archive.ubuntu.com/ubuntu noble/main amd64 cmake-data all 3.28.3-1build7 [2,155 kB]
Get:4 http://archive.ubuntu.com/ubuntu noble/main amd64 cmake amd64 3.28.3-1build7 [11.2 MB]
Fetched 13.6 MB in 2s (5,610 kB/s)
Selecting previously unselected package libjsoncpp25:amd64.
(Reading database ... 426094 files and directories currently installed.)
Preparing to unpack .../libjsoncpp25_1.9.5-6build1_amd64.deb ...
Unpacking libjsoncpp25:amd64 (1.9.5-6build1) ...
Selecting previously unselected package librhash0:amd64.
Preparing to unpack .../librhash0_1.4.3-3build1_amd64.deb ...
Unpacking librhash0:amd64 (1.4.3-3build1) ...
Selecting previously unselected package cmake-data.
Preparing to unpack .../cmake-data_3.28.3-1build7_all.deb ...
Unpacking cmake-data (3.28.3-1build7) ...
Selecting previously unselected package cmake.
Preparing to unpack .../cmake_3.28.3-1build7_amd64.deb ...
Unpacking cmake (3.28.3-1build7) ...
Setting up libjsoncpp25:amd64 (1.9.5-6build1) ...
Setting up librhash0:amd64 (1.4.3-3build1) ...
Setting up cmake-data (3.28.3-1build7) ...
Setting up cmake (3.28.3-1build7) ...
Processing triggers for man-db (2.12.0-4build2) ...
Processing triggers for libc-bin (2.39-0ubuntu8.6) ...
```
### MacOS

```sh
$ brew install cmake
==> Fetching cmake
==> Downloading https://ghcr.io/v2/homebrew/core/cmake/blobs/sha256:a9a87dd3bdc0751b398eb60ca9bbbdb35a494478423af6b5a1ecc3594df48f6
Already downloaded: /Users/asangdani/Library/Caches/Homebrew/downloads/897f09b729907e31e9e5a32572a6a4ead9498431573ca867d72631540a684860--cmake--4.1.2.arm64_tahoe.bottle.tar.gz
==> Pouring cmake--4.1.2.arm64_tahoe.bottle.tar.gz
==> Caveats
To install the CMake documentation, run:
  brew install cmake-docs
==> Summary
 /opt/homebrew/Cellar/cmake/4.1.2: 3,913 files, 58.2MB
==> Running `brew cleanup cmake`...
Disable this behaviour by setting `HOMEBREW_NO_INSTALL_CLEANUP=1`.
Hide these hints with `HOMEBREW_NO_ENV_HINTS=1` (see `man brew`).
==> Caveats
Emacs Lisp files have been installed to:
  /opt/homebrew/share/emacs/site-lisp/cmake
```

## How to use cmake?

To get started, you need to create `CMakeLists.txt` file (in the same directory as your test pogram `test.cpp`) as follows:
```cmake
cmake_minimum_required(VERSION 3.11)
project(test)
add_executable(test test.cpp)
```

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

## More advanced example

In real C++ programs, you don't write all the code in just one file! If I am sounding too naiive, believe me that I see this all the time when I talk to students. This is not maintainable. You typically develop large sofware as independent components that are built into `shared libraries` that are then integrated and used to build one large functional program. Here is how can can organize a program:

```sh
├── CMakeLists.txt
├── cpphello.cpp
├── helloprint.cpp
├── helloprint.h
└── hello_test.cpp
```

Here, `helloprint.h` provides a simple API `get_hello`. The API is implemented in `helloprint.cpp`. I want to make sure that this wonderful API can be used in other places and not just `cpphello.cpp` program. I went ahead and create a `CMakeLists.txt` as follows:

### helloprint.h

```c++
#ifndef _hello_print_h_
#define _hello_print_h_

#include <string>

extern const std::string get_hello();

#endif // _hello_print_h_
```

### helloprint.cpp

```c++
#include "helloprint.h"

const std::string
get_hello()
{
    return "Hello World Indeed!";
}
```

### cpphello.cpp

```c++
#include <iostream>
#include "helloprint.h"

int
main()
{
    std::cout << get_hello() << std::endl;
    return 0;
}
```

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.11)

project(cpphello VERSION 0.1 DESCRIPTION "hello world")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(cpphello cpphello.cpp)
add_library(helloprint SHARED helloprint.cpp helloprint.h)
target_link_libraries(cpphello helloprint)
```

In order to build the program run following commands:

```sh
$ cmake -S . -B build
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
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
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/asang/sysprog-workshop/cmakedemo/progwithtest/build

$ cmake --build build
(base) asang@amd-server:~/sysprog-workshop/cmakedemo/progwithtest$ cmake --build build
/usr/bin/cmake -S/home/asang/sysprog-workshop/cmakedemo/progwithtest -B/home/asang/sysprog-workshop/cmakedemo/progwithtest/build --                                                                                check-build-system CMakeFiles/Makefile.cmake 0
/usr/bin/cmake -E cmake_progress_start /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CMakeFiles /home/asang/sysprog-wor                                                                                kshop/cmakedemo/progwithtest/build//CMakeFiles/progress.marks
/usr/bin/gmake  -f CMakeFiles/Makefile2 all
gmake[1]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/helloprint.dir/build.make CMakeFiles/helloprint.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/syspro                                                                                g-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwi                                                                                thtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CM                                                                                akeFiles/helloprint.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/helloprint.dir/build.make CMakeFiles/helloprint.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 25%] Building CXX object CMakeFiles/helloprint.dir/helloprint.cpp.o
/usr/bin/c++ -Dhelloprint_EXPORTS  -std=gnu++14 -fPIC -MD -MT CMakeFiles/helloprint.dir/helloprint.cpp.o -MF CMakeFiles/helloprint.                                                                                dir/helloprint.cpp.o.d -o CMakeFiles/helloprint.dir/helloprint.cpp.o -c /home/asang/sysprog-workshop/cmakedemo/progwithtest/hellopr                                                                                int.cpp
[ 50%] Linking CXX shared library libhelloprint.so
/usr/bin/cmake -E cmake_link_script CMakeFiles/helloprint.dir/link.txt --verbose=1
/usr/bin/c++ -fPIC -shared -Wl,-soname,libhelloprint.so -o libhelloprint.so CMakeFiles/helloprint.dir/helloprint.cpp.o
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 50%] Built target helloprint
/usr/bin/gmake  -f CMakeFiles/cpphello.dir/build.make CMakeFiles/cpphello.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/syspro                                                                                g-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwi                                                                                thtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CM                                                                                akeFiles/cpphello.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/cpphello.dir/build.make CMakeFiles/cpphello.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 75%] Building CXX object CMakeFiles/cpphello.dir/cpphello.cpp.o
/usr/bin/c++   -std=gnu++14 -MD -MT CMakeFiles/cpphello.dir/cpphello.cpp.o -MF CMakeFiles/cpphello.dir/cpphello.cpp.o.d -o CMakeFil                                                                                es/cpphello.dir/cpphello.cpp.o -c /home/asang/sysprog-workshop/cmakedemo/progwithtest/cpphello.cpp
[100%] Linking CXX executable cpphello
/usr/bin/cmake -E cmake_link_script CMakeFiles/cpphello.dir/link.txt --verbose=1
/usr/bin/c++ CMakeFiles/cpphello.dir/cpphello.cpp.o -o cpphello  -Wl,-rpath,/home/asang/sysprog-workshop/cmakedemo/progwithtest/bui                                                                                ld libhelloprint.so
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[100%] Built target cpphello
gmake[1]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/cmake -E cmake_progress_start /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CMakeFiles 0
```

Lets see the hierarchy of generated files in `build` folder:
```sh
$ tree build

├── CMakeCache.txt
├── CMakeFiles
│   ├── 3.28.3
│   │   ├── CMakeCCompiler.cmake
│   │   ├── CMakeCXXCompiler.cmake
│   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   ├── CMakeSystem.cmake
│   │   ├── CompilerIdC
│   │   │   ├── a.out
│   │   │   ├── CMakeCCompilerId.c
│   │   │   └── tmp
│   │   └── CompilerIdCXX
│   │       ├── a.out
│   │       ├── CMakeCXXCompilerId.cpp
│   │       └── tmp
│   ├── cmake.check_cache
│   ├── CMakeConfigureLog.yaml
│   ├── CMakeDirectoryInformation.cmake
│   ├── CMakeScratch
│   ├── cpphello.dir
│   │   ├── build.make
│   │   ├── cmake_clean.cmake
│   │   ├── compiler_depend.make
│   │   ├── compiler_depend.ts
│   │   ├── cpphello.cpp.o
│   │   ├── cpphello.cpp.o.d
│   │   ├── DependInfo.cmake
│   │   ├── depend.make
│   │   ├── flags.make
│   │   ├── link.txt
│   │   └── progress.make
│   ├── helloprint.dir
│   │   ├── build.make
│   │   ├── cmake_clean.cmake
│   │   ├── compiler_depend.make
│   │   ├── compiler_depend.ts
│   │   ├── DependInfo.cmake
│   │   ├── depend.make
│   │   ├── flags.make
│   │   ├── helloprint.cpp.o
│   │   ├── helloprint.cpp.o.d
│   │   ├── link.txt
│   │   └── progress.make
│   ├── Makefile2
│   ├── Makefile.cmake
│   ├── pkgRedirects
│   ├── progress.marks
│   └── TargetDirectories.txt
├── cmake_install.cmake
├── cpphello
├── libhelloprint.so
└── Makefile
```

Notice that shared library `libhelloprint.so` has been generated and linked against `cpphello`. How do we see that?
```sh
$ cd build && ldd cpphello
     linux-vdso.so.1 (0x00007bd764853000)
     libhelloprint.so => /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/libhelloprint.so (0x00007bd764843000)
     libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007bd764400000)
     libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007bd7647fd000)
     libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007bd764000000)
     libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007bd764714000)
     /lib64/ld-linux-x86-64.so.2 (0x00007bd764855000)
```
`ldd` shows shared libraries an executable depends on.

## Automated testing with googletest

Unit testing is part of the software development lifecycle for every developer. There are several ways to do it. For C++ there in extremely popular option [GoogleTest](https://github.com/google/googletest) that is widely used. We will see a simple example of it and how it integrated with our example. Before explaining everything else, lets see the test program:

### hello_test.cpp

```c++
#include <gtest/gtest.h>
#include "helloprint.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE( "hello", get_hello().c_str() );
  EXPECT_STREQ( "Hello World Indeed!", get_hello().c_str() );
}
```

As you can see the test program has two expectations - first is that `get_hello` function does not a string `hello` and second that it returns `Hello World Indeed!`. To integrate it with your `cmake` based system, just add following lines at the end of your `CMakeLists.txt` file:

```cmake
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test PRIVATE
  GTest::gtest_main
  helloprint
)

include(GoogleTest)
gtest_discover_tests(hello_test)
```

To build and run the tests, just execute:

```sh
$ cmake --build build
/usr/bin/cmake -S/home/asang/sysprog-workshop/cmakedemo/progwithtest -B/home/asang/sysprog-workshop/cmakedemo/progwithtest/build --check-build-system CMakeFiles/Makefile.cmake 0
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (2.9s)
-- Generating done (0.0s)
-- Build files have been written to: /home/asang/sysprog-workshop/cmakedemo/progwithtest/build
/usr/bin/cmake -E cmake_progress_start /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CMakeFiles /home/asang/sysprog-workshop/cmakedemo/progwithtest/build//CMakeFiles/progress.marks
/usr/bin/gmake  -f CMakeFiles/Makefile2 all
gmake[1]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/helloprint.dir/build.make CMakeFiles/helloprint.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CMakeFiles/helloprint.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/helloprint.dir/build.make CMakeFiles/helloprint.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
gmake[2]: Nothing to be done for 'CMakeFiles/helloprint.dir/build'.
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 14%] Built target helloprint
/usr/bin/gmake  -f CMakeFiles/cpphello.dir/build.make CMakeFiles/cpphello.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CMakeFiles/cpphello.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/cpphello.dir/build.make CMakeFiles/cpphello.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/cpphello.dir/build.make CMakeFiles/cpphello.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
gmake[2]: Nothing to be done for 'CMakeFiles/cpphello.dir/build'.
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 28%] Built target cpphello
/usr/bin/gmake  -f _deps/googletest-build/googletest/CMakeFiles/gtest.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest/CMakeFiles/gtest.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f _deps/googletest-build/googletest/CMakeFiles/gtest.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 35%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest && /usr/bin/c++  -I/home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest/include -I/home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest -std=c++14 -Wall -Wshadow -Wundef -Wno-error=dangling-else -DGTEST_HAS_PTHREAD=1 -fexceptions -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -MD -MT _deps/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o -MF CMakeFiles/gtest.dir/src/gtest-all.cc.o.d -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest/src/gtest-all.cc
[ 42%] Linking CXX static library ../../../lib/libgtest.a
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest && /usr/bin/cmake -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest && /usr/bin/cmake -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=1
/usr/bin/ar qc ../../../lib/libgtest.a "CMakeFiles/gtest.dir/src/gtest-all.cc.o"
/usr/bin/ranlib ../../../lib/libgtest.a
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 42%] Built target gtest
/usr/bin/gmake  -f _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/build.make _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 50%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest && /usr/bin/c++  -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest/include -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest -std=c++14 -Wall -Wshadow -Wundef -Wno-error=dangling-else -DGTEST_HAS_PTHREAD=1 -fexceptions -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -MD -MT _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o -MF CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.d -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.o -c /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest/src/gtest_main.cc
[ 57%] Linking CXX static library ../../../lib/libgtest_main.a
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest && /usr/bin/cmake -P CMakeFiles/gtest_main.dir/cmake_clean_target.cmake
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googletest && /usr/bin/cmake -E cmake_link_script CMakeFiles/gtest_main.dir/link.txt --verbose=1
/usr/bin/ar qc ../../../lib/libgtest_main.a CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
/usr/bin/gmake  -f CMakeFiles/hello_test.dir/build.make CMakeFiles/hello_test.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CMakeFiles/hello_test.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f CMakeFiles/hello_test.dir/build.make CMakeFiles/hello_test.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 64%] Building CXX object CMakeFiles/hello_test.dir/hello_test.cpp.o
/usr/bin/c++  -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest/include -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest -std=gnu++14 -MD -MT CMakeFiles/hello_test.dir/hello_test.cpp.o -MF CMakeFiles/hello_test.dir/hello_test.cpp.o.d -o CMakeFiles/hello_test.dir/hello_test.cpp.o -c /home/asang/sysprog-workshop/cmakedemo/progwithtest/hello_test.cpp
[ 71%] Linking CXX executable hello_test
/usr/bin/cmake -E cmake_link_script CMakeFiles/hello_test.dir/link.txt --verbose=1
/usr/bin/c++ CMakeFiles/hello_test.dir/hello_test.cpp.o -o hello_test  -Wl,-rpath,/home/asang/sysprog-workshop/cmakedemo/progwithtest/build lib/libgtest_main.a libhelloprint.so lib/libgtest.a
/usr/bin/cmake -D TEST_TARGET=hello_test -D TEST_EXECUTABLE=/home/asang/sysprog-workshop/cmakedemo/progwithtest/build/hello_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/asang/sysprog-workshop/cmakedemo/progwithtest/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=hello_test_TESTS -D CTEST_FILE=/home/asang/sysprog-workshop/cmakedemo/progwithtest/build/hello_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.28/Modules/GoogleTestAddTests.cmake
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 71%] Built target hello_test
/usr/bin/gmake  -f _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/build.make _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/depend
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/asang/sysprog-workshop/cmakedemo/progwithtest /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googlemock /home/asang/sysprog-workshop/cmakedemo/progwithtest/build /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock/CMakeFiles/gmock.dir/DependInfo.cmake "--color="
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/gmake  -f _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/build.make _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/build
gmake[2]: Entering directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 78%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock && /usr/bin/c++  -I/home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googlemock/include -I/home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googlemock -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest/include -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest -std=c++14 -Wall -Wshadow -Wundef -Wno-error=dangling-else -DGTEST_HAS_PTHREAD=1 -fexceptions -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -MD -MT _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o -MF CMakeFiles/gmock.dir/src/gmock-all.cc.o.d -o CMakeFiles/gmock.dir/src/gmock-all.cc.o -c /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googlemock/src/gmock-all.cc
^[[A[ 85%] Linking CXX static library ../../../lib/libgmock.a
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock && /usr/bin/cmake -P CMakeFiles/gmock.dir/cmake_clean_target.cmake
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock && /usr/bin/cmake -E cmake_link_script CMakeFiles/gmock.dir/link.txt --verbose=1
/usr/bin/ar qc ../../../lib/libgmock.a "CMakeFiles/gmock.dir/src/gmock-all.cc.o"
/usr/bin/ranlib ../../../lib/libgmock.a
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[ 92%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock && /usr/bin/c++  -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googlemock/include -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googlemock -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest/include -isystem /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googletest -std=c++14 -Wall -Wshadow -Wundef -Wno-error=dangling-else -DGTEST_HAS_PTHREAD=1 -fexceptions -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -MD -MT _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o -MF CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.d -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.o -c /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-src/googlemock/src/gmock_main.cc
[100%] Linking CXX static library ../../../lib/libgmock_main.a
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock && /usr/bin/cmake -P CMakeFiles/gmock_main.dir/cmake_clean_target.cmake
cd /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/_deps/googletest-build/googlemock && /usr/bin/cmake -E cmake_link_script CMakeFiles/gmock_main.dir/link.txt --verbose=1
/usr/bin/ar qc ../../../lib/libgmock_main.a CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
/usr/bin/ranlib ../../../lib/libgmock_main.a
gmake[2]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
[100%] Built target gmock_main
gmake[1]: Leaving directory '/home/asang/sysprog-workshop/cmakedemo/progwithtest/build'
/usr/bin/cmake -E cmake_progress_start /home/asang/sysprog-workshop/cmakedemo/progwithtest/build/CMakeFiles 0
```

To test it, run:
```sh
$ cmake --build build --target test

Running tests...
/usr/bin/ctest --force-new-ctest-process
Test project /home/asang/sysprog-workshop/cmakedemo/progwithtest/build
    Start 1: HelloTest.BasicAssertions
1/1 Test #1: HelloTest.BasicAssertions ........   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```
