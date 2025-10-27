# What is cmake and why use it?

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
