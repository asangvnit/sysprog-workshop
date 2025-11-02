<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [What Every Programmer Should Know..](#what-every-programmer-should-know)
  - [CPU and Memory](#cpu-and-memory)
  - [Type of Caches](#type-of-caches)
    - [Direct Mapped](#direct-mapped)
    - [Fully Associative](#fully-associative)
    - [Set Associative](#set-associative)
  - [L1 Cache](#l1-cache)
  - [Cost of Memory Access](#cost-of-memory-access)
  - [References](#references)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# What Every Programmer Should Know..

Almost all modern systems use Memory Hierarchies. Understanding how interaction between CPU and memory hierarchy works and programming with `cache friendliness` in mind has a profound impact on performance of your application and how you choose, design, and tune your data structures.

Most basic Operating System courses teach how Virtual Memory is employed by Operating Systems. So we will skip that description here. It suffices to know that the memory layout/map of a process is different on different operating systems and also depends on the type of CPU. For 64-bit linux, [x86_64](https://www.kernel.org/doc/Documentation/x86/x86_64/mm.txt) and [arm64](https://www.kernel.org/doc/Documentation/arm64/memory.txt) platforms, it can be quite different. Here we will focus primarily on how modern CPUs work with caches and how that affects the system performance. A typical process memory layout is as follows:
```mermaid
graph TD
    subgraph User_Space["User Space"]
        A[Process]
        A1[Code - Text Segment]
        A2[Data - Initialized Data]
        A3[BSS - Uninitialized Data]
        A4[Heap - malloc/new]
        A5[Stack - Function Calls, Local Vars]
        A6[Shared Libraries - libc, libm, etc.]
    end

    subgraph Kernel_Space["Kernel Space"]
        K1[Task_struct #40;Process Control Block#41;]
        K2[Kernel Stack #40;Per-Process Stack#41;]
        K3[File Descriptors]
        K4[Memory Mappings #40;VMAs#41;]
        K5[Scheduler]
        K6[System Calls Interface]
    end

    subgraph Hardware["CPU & Memory"]
        H1[MMU #40;Memory Management Unit#41;]
        H2[CPU Registers]
        H3[Page Tables]
    end

    %% Relationships
    A -->|exec#40;#41;, fork#40;#41;, clone#40;#41;| K1
    A -->|syscalls #40;read, write, open, etc.#41;| K6
    K6 --> K5
    K1 --> K2
    K1 --> K3
    K1 --> K4
    K4 --> H3
    H3 --> H1
    H1 --> H2

    %% Additional concepts
    A5 -->|function calls| A1
    A4 -->|dynamic allocation| K4
    A6 -->|loaded via ld.so| A

    %% Styles
    classDef user fill:#d0f0ff,stroke:#0077b6,stroke-width:1px;
    classDef kernel fill:#ffd6a5,stroke:#e67e22,stroke-width:1px;
    classDef hardware fill:#d3f8d3,stroke:#28a745,stroke-width:1px;

    class A,A1,A2,A3,A4,A5,A6 user;
    class K1,K2,K3,K4,K5,K6 kernel;
    class H1,H2,H3 hardware;
```

## CPU and Memory

Typical hierachical memory structure with caching model and sizes is shown below. Caching works on the principle of temporal and spatial locality of reference. Lower the level, faster the access and closeness to the CPU. Lower level caches are smaller and more expensive. e.g. L1 caches are more expensive than L2 caches.

```mermaid
graph TB
    CPU["CPU Core"]

    subgraph CACHES["Cache Hierarchy (per core / shared)"]
        direction TB
        L1["L1 Cache<br/>32 KB · 8-way · ~4 cycles<br/>(Private, I/D split)"]
        L2["L2 Cache<br/>256 KB · 8-way · ~12 cycles<br/>(Private or per-core)"]
        L3["L3 Cache<br/>8 MB · 16-way · ~30–50 cycles<br/>(Shared, last-level)"]
    end

    MEM["Main Memory (DRAM)<br/>8-64 GB . ~50–150 ns"]

    CPU -->|load/store| L1
    L1 -->|miss| L2
    L2 -->|miss| L3
    L3 -->|miss| MEM

    L1 -->|hit| CPU
    L2 -->|hit| CPU
    L3 -->|hit| CPU
```
## Type of Caches

### Direct Mapped

Any memory block can map onto one fixed cache line. These are easier to build but cache performance is not great due to high likelihood of collisons.

```mermaid
graph TB
    subgraph MAINMEM["Main Memory"]
        A0["Block 0"]
        A1["Block 1"]
        A2["Block 2"]
        A3["Block 3"]
        A4["Block 4"]
        A5["Block 5"]
    end

    subgraph CACHE["Direct-Mapped Cache"]
        C0["Line 0"]
        C1["Line 1"]
        C2["Line 2"]
    end

    %% Mapping of blocks to cache lines
    A0 --> C0
    A3 --> C0
    A1 --> C1
    A4 --> C1
    A2 --> C2
    A5 --> C2
```

### Fully Associative

Any memory block can map onto any cache line. Flexible but expensive to build as we must compare the *tag* against all the entries in the cache.

```mermaid
graph TB
    subgraph MAINMEM["Main Memory"]
        B1["Block 0"]
        B2["Block 1"]
        B3["Block 2"]
        B4["Block 3"]
    end

    subgraph CACHE["Fully Associative Cache"]
        F1["Line 0"]
        F2["Line 1"]
        F3["Line 2"]
        F4["Line 3"]
    end

    B1 --> F1
    B1 --> F2
    B1 --> F3
    B1 --> F4

    B2 --> F1
    B2 --> F2
    B2 --> F3
    B2 --> F4
```

### Set Associative

Cache is split into sets, each with multiple *ways* or lines. Balances flexibility and hardware cost. Typical in modern CPUs (8-way is common for L1).

```mermaid
graph TB
    subgraph MAINMEM["Main Memory"]
        C1["Block 0"]
        C2["Block 1"]
        C3["Block 2"]
        C4["Block 3"]
        C5["Block 4"]
    end

    subgraph CACHE["2-Way Set Associative Cache"]
        subgraph Set0["Set 0"]
            S0W0["Way 0"]
            S0W1["Way 1"]
        end
        subgraph Set1["Set 1"]
            S1W0["Way 0"]
            S1W1["Way 1"]
        end
    end

    C1 --> Set0
    C2 --> Set1
    C3 --> Set0
    C4 --> Set1
    C5 --> Set0
```

## L1 Cache
- Separate Instruction and Data Cache
- Typical size of single line - 64 bytes
- Number of cache lines = 32 kB / 64 = 512
- 8 way means 512 / 8 = 64 sets.
- Lowest 8 bit of the address correspond to an offset within a cache line and next 8 bits *implicitly* correspond to the set. Upper 16 bits (in case of 32-bit addrss) correspond to Tag bits - which are stored for each cache entry.
- Multiple addresses *alias* to the same set within cache. with 8 way-associative caches when comparing Tag bits within an address, comparison with Tags for all 8 cache lines within a set are compared parallely for efficiency.

## Cost of Memory Access

| Memory Level       | Access Time (cycles) | Typical Size  | Notes                                                  |
| ------------------ | -------------------- | ------------- | ------------------------------------------------------ |
| L1 Cache           | 3 – 5                | 32–128 KB     | Fastest, private to core, VIPT (Virtually Indexed, Physically Tagged) indexing                |
| L2 Cache           | 10 – 20              | 256 KB – 1 MB | Private to core or cluster, slower than L1             |
| L3 Cache           | 30 – 50              | 2–64 MB       | Shared between cores, physically indexed               |
| Main Memory (DRAM) | 50 – 150             | GBs           | Orders of magnitude slower, physical address access    |
| SSD/NVMe Storage   | 100K – 1M            | TBs           | Persistent storage, accessed via OS/hardware interface |
| HDD                | 1M – 10M             | TBs           | Much slower, mechanical latency dominates              |

## References

- [What Every Programmer Should Know About Memory](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)
