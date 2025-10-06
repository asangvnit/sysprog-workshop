# How to use cmake?

In the current directory, run:

```sh
cmake -S . -B build
cmake --build build
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
