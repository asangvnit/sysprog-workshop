<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Leaks, locks and much more](#leaks-locks-and-much-more)
- [Simple example](#simple-example)
- [Cachegrind - cache and branch profiler](#cachegrind---cache-and-branch-profiler)
- [Other useful tools](#other-useful-tools)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Leaks, locks and much more

When writing large programs that run in the background - servers/services, its is not enough to validate that they function correctly. It is extremely important to ensure that they do not *Leak* resources. Resource leaks can be any one of the following:

- Memory Leaks - Forgetting to free memory that is no longer used.
- File descriptor leaks - Forgetting to close the files that we are no longer using.
- Networking socket leaks - Unused sockets that we forget to close.

In addition, multi-threaded programs can potentially deadlock due to inability to aquire locks due to circular dependencies or forgetting to release a lock.

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

## Cachegrind - cache and branch profiler
Valgrind supports tool called `cachegrind` that helps identify problems with modern programs that interact poorly with [CPU caches](../Memory.md) and processor branch prediction and reports cache misses and branch mispredictions. Consider following example where we run the `bottlenecks-mt` command under `valgrind --tool=cachegrind`.
```sh
ubuntu@sysprog:/sysprog/perf-demo$ valgrind --tool=cachegrind --verbose --cache-sim=yes --branch-sim=yes ./bottlenecks-mt
==3140== Cachegrind, a high-precision tracing profiler
==3140== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
==3140== Using Valgrind-3.22.0-bd4db67b1d-20231031 and LibVEX; rerun with -h for copyright info
==3140== Command: ./bottlenecks-mt
==3140==
--3140-- Valgrind options:
--3140--    --tool=cachegrind
--3140--    --verbose
--3140--    --cache-sim=yes
--3140--    --branch-sim=yes
--3140-- Contents of /proc/version:
--3140--   Linux version 6.8.0-85-generic (buildd@bos03-arm64-027) (aarch64-linux-gnu-gcc-13 (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0, GNU ld (GNU Binutils for Ubuntu) 2.42) #85-Ubuntu SMP PREEMPT_DYNAMIC Thu Sep 18 15:21:04 UTC 2025
--3140--
--3140-- Arch and hwcaps: ARM64, LittleEndian, v8-fhm-dpbcvadp-sha3-rdm-atomics-fp16-vfp16
--3140-- Page sizes: currently 4096, max supported 65536
--3140-- Valgrind library directory: /usr/libexec/valgrind
--3140-- Warning: Cannot auto-detect cache config, using defaults.
--3140--          Run with -v to see.
==3140== Cache configuration used:
==3140==   I1: 16,384 B, 4-way, 64 B lines
==3140==   D1: 16,384 B, 4-way, 64 B lines
==3140==   LL: 262,144 B, 8-way, 64 B lines
...

...
Using 4 threads.

[CPU-bound]
Primes found: 2262

[Memory-bound]
Matrix multiplication done for size 300x300

[I/O-bound]
File written with 200000 lines.

Total time: 11.332 s
==3140==
==3140== I refs:        1,996,681,571
==3140== I1  misses:        1,809,875
==3140== LLi misses:            4,275
==3140== I1  miss rate:          0.09%
==3140== LLi miss rate:          0.00%
==3140==
==3140== D refs:          278,579,118  (188,110,420 rd   + 90,468,698 wr)
==3140== D1  misses:       40,705,663  ( 40,641,395 rd   +     64,268 wr)
==3140== LLd misses:        3,489,796  (  3,429,443 rd   +     60,353 wr)
==3140== D1  miss rate:          14.6% (       21.6%     +        0.1%  )
==3140== LLd miss rate:           1.3% (        1.8%     +        0.1%  )
==3140==
==3140== LL refs:          42,515,538  ( 42,451,270 rd   +     64,268 wr)
==3140== LL misses:         3,494,071  (  3,433,718 rd   +     60,353 wr)
==3140== LL miss rate:            0.2% (        0.2%     +        0.1%  )
==3140==
==3140== Branches:        206,044,722  (200,355,579 cond +  5,689,143 ind)
==3140== Mispredicts:       2,659,476  (  2,257,898 cond +    401,578 ind)
==3140== Mispred rate:            1.3% (        1.1%     +        7.1%   )
```
It takes some effort to understand the acronym soup here.
- I1 misses = instruction cache misses at L1
- D1 misses = data cache misses at L1
- LLi / LLd misses = how many of those went all the way to the Last Level cache and still missed
- LL refs = total number of last-level cache accesses (misses from L1)

For the branch prediction section `cond` - Conditional branches, `ind` - Indirect branches. Running the above command also produces a file like `cachegrind.out.3140`. This can be used to annotate the source code for further analysis of where the issues are.
```sh
ubuntu@sysprog:/sysprog/perf-demo$ cg_annotate cachegrind.out.3140
-- Metadata
--------------------------------------------------------------------------------
Invocation:       /usr/bin/cg_annotate cachegrind.out.3140
I1 cache:         16384 B, 64 B, 4-way associative
D1 cache:         16384 B, 64 B, 4-way associative
LL cache:         262144 B, 64 B, 8-way associative
Command:          ./bottlenecks-mt
Events recorded:  Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw Bc Bcm Bi Bim
Events shown:     Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw Bc Bcm Bi Bim
Event sort order: Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw Bc Bcm Bi Bim
Threshold:        0.1%
Annotation:       on

--------------------------------------------------------------------------------
-- Summary
--------------------------------------------------------------------------------
Ir____________________ I1mr______________ ILmr__________ Dr__________________ D1mr_______________ DLmr______________ Dw_________________ D1mw___________ DLmw___________ Bc__________________ Bcm_______________ Bi________________ Bim_____________

1,996,681,571 (100.0%) 1,809,875 (100.0%) 4,275 (100.0%) 188,110,420 (100.0%) 40,641,395 (100.0%) 3,429,443 (100.0%) 90,468,698 (100.0%) 64,268 (100.0%) 60,353 (100.0%) 200,355,579 (100.0%) 2,257,898 (100.0%) 5,689,143 (100.0%) 401,578 (100.0%)  PROGRAM TOTALS

--------------------------------------------------------------------------------
-- File:function summary
--------------------------------------------------------------------------------
  Ir__________________________ I1mr____________________ ILmr________________ Dr_______________________ D1mr______________________ DLmr____________________ Dw_______________________ D1mw_________________ DLmw_________________ Bc________________________ Bcm_____________________ Bi________________________ Bim___________________  file:function
...
    524,880,000 (26.3%)          180,017  (9.9%)           18  (0.4%)        15,120,000  (8.0%)                 0                         0                15,120,000 (16.7%)             0                     0                 72,720,000 (36.3%)               52  (0.0%)                0                        0                   __multf3
    231,120,000 (11.6%)          180,021  (9.9%)           22  (0.5%)         1,080,000  (0.6%)                 0                         0                 1,080,000  (1.2%)             0                     0                 33,840,000 (16.9%)        1,080,047 (47.8%)                0                        0                   __addtf3
    199,800,000 (10.0%)               16  (0.0%)           16  (0.4%)                 0                         0                         0                         0                     0                     0                 29,520,000 (14.7%)          720,026 (31.9%)                0                        0                   __subtf3
     53,280,000  (2.7%)          360,026 (19.9%)           28  (0.7%)         1,440,000  (0.8%)                 1  (0.0%)                 1  (0.0%)         1,080,000  (1.2%)             0                     0                  5,760,000  (2.9%)               21  (0.0%)          360,000   (6.3%)               1  (0.0%)           __divtf3
     35,294,103  (1.8%)            1,161  (0.1%)          372  (8.7%)         7,418,008  (3.9%)             1,055  (0.0%)               191  (0.0%)         2,289,633  (2.5%)            39  (0.1%)            28  (0.0%)          1,489,108  (0.7%)               85  (0.0%)        4,328,340  (76.1%)         401,291 (99.9%)           ???
     17,200,344  (0.9%)               29  (0.0%)           16  (0.4%)         4,400,088  (2.3%)                 3  (0.0%)                 0                 3,600,072  (4.0%)             4  (0.0%)             0                  1,400,028  (0.7%)               14  (0.0%)          200,004   (3.5%)               3  (0.0%)           std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const
...
```
Complete output can be found in [cachegrind-output.txt](../perf-demo/cachegrind-output.txt). In order to understand symbologies here, see the table below:

| Symbol | Meaning                | Type of Cache                      |
| ------ | ---------------------- | ---------------------------------- |
| **D**  | Data cache             | Refers to data (not instructions)  |
| **I**  | Instruction cache      | Refers to code fetches             |
| **1**  | Level 1 cache          | The first-level cache              |
| **L**  | Last-level cache (LLC) | Usually L3                         |
| **r**  | Read miss              | A read operation missed the cache  |
| **w**  | Write miss             | A write operation missed the cache |
| **mr** | Miss read              | (shorthand combined form)          |

Some more symbols for those brave souls!

| Code     | Meaning                                |
| -------- | -------------------------------------- |
| **D1mr** | Data L1 cache read miss                |
| **D1mw** | Data L1 cache write miss               |
| **DLmr** | Data last-level cache read miss        |
| **DLmw** | Data last-level cache write miss       |
| **I1mr** | Instruction L1 cache read miss         |
| **ILmr** | Instruction last-level cache read miss |

In order ot understand branch prediction stats, see this:

| Code    | Meaning                           | Description                                                                                              |
| ------- | --------------------------------- | -------------------------------------------------------------------------------------------------------- |
| **BIm** | *Conditional branch mispredicted* | CPU guessed wrong on an `if`, `for`, or `while` branch. Pipeline flush → several lost cycles.            |
| **BIc** | *Conditional branch executed*     | Total conditional branches actually run (not just taken). Useful as the denominator for mispredict rate. |
| **Bcm** | *Indirect branch mispredicted*    | CPU guessed wrong on an *indirect* jump, e.g. a function pointer or virtual call. Often expensive.       |
| **Bcc** | *Indirect branch executed*        | Total number of indirect branches executed.                                                              |
| **BTm** | *Total branches mispredicted*     | Aggregate of conditional + indirect mispredictions.                                                      |
| **BTc** | *Total branches executed*         | Aggregate of conditional + indirect executed branches.                                                   |

## Other useful tools

- [pstack](https://linux.die.net/man/1/pstack) prints a stacktrace of a running process
- [lsof](https://www.man7.org/linux/man-pages/man8/lsof.8.html) list open files
- [netstat](https://linux.die.net/man/8/netstat) Print network connections, routing tables, interface statistics
