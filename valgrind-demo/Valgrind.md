# Leaks, locks and much more

[Valgrind](https://valgrind.org/) is an instrumentation framework for building dynamic analysis tools. Valgrind tools can automatically detect many memory management and threading bugs, and profile your programs in detail.

## Simple example 

```C
#include <stdlib.h>

void f(void)
{
   int* x = malloc(10 * sizeof(int));
   x[10] = 0;        // problem 1: heap block overrun
}                    // problem 2: memory leak -- x not freed

int main(void)
{
   f();
   return 0;
}
```
Save this file as `test.c` and compile it
```sh
gcc -g test.c -o test
```
Run it under valgrind leak checker
```sh
$ valgrind --leak-check=yes ./test
==4122746== Memcheck, a memory error detector
==4122746== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==4122746== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==4122746== Command: ./test
==4122746==
==4122746== Invalid write of size 4
==4122746==    at 0x10916B: f (test.c:6)
==4122746==    by 0x109180: main (test.c:11)
==4122746==  Address 0x4a87068 is 0 bytes after a block of size 40 alloc'd
==4122746==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4122746==    by 0x10915E: f (test.c:5)
==4122746==    by 0x109180: main (test.c:11)
==4122746==
==4122746==
==4122746== HEAP SUMMARY:
==4122746==     in use at exit: 40 bytes in 1 blocks
==4122746==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==4122746==
==4122746== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==4122746==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4122746==    by 0x10915E: f (test.c:5)
==4122746==    by 0x109180: main (test.c:11)
==4122746==
==4122746== LEAK SUMMARY:
==4122746==    definitely lost: 40 bytes in 1 blocks
==4122746==    indirectly lost: 0 bytes in 0 blocks
==4122746==      possibly lost: 0 bytes in 0 blocks
==4122746==    still reachable: 0 bytes in 0 blocks
==4122746==         suppressed: 0 bytes in 0 blocks
==4122746==
==4122746== For lists of detected and suppressed errors, rerun with: -s
==4122746== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```
It clearly shows both the issues: heap overrun on line 6 and leaked memory on line 5.
