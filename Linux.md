# Introduction to linux

Most widely used **NIX based operating system in the world today. Has many variants and forks - but `debian`, `ubuntu` and `fedora` are some of the most widely used ones. You can install it on your laptop directly. Detailed instructions can be found in [Setup](Setup.md). Please follow those instructions (if you haven't done so already and then come back here).

First, you connect to the `multipass ubuntu` instance you had created earlier (Those running on Windows can omit `sudo` on Window cmd prompt).

```sh
$ sudo multipass shell sysprog
Welcome to Ubuntu 24.04.3 LTS (GNU/Linux 6.8.0-85-generic aarch64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/pro

 System information as of Mon Oct 20 10:18:25 IST 2025

  System load:             0.0
  Usage of /:              22.6% of 8.65GB
  Memory usage:            5%
  Swap usage:              0%
  Processes:               129
  Users logged in:         0
  IPv4 address for enp0s1: 192.168.2.2
  IPv6 address for enp0s1: fdb0:2327:1cc6:cbf2:5054:ff:feaf:db7


Expanded Security Maintenance for Applications is not enabled.

14 updates can be applied immediately.
To see these additional updates run: apt list --upgradable

Enable ESM Apps to receive additional future security updates.
See https://ubuntu.com/esm or run: sudo pro status


To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

ubuntu@sysprog:~$
```

For system version details, run

```sh
ubuntu@sysprog:~$ uname -a
Linux sysprog 6.8.0-85-generic #85-Ubuntu SMP PREEMPT_DYNAMIC Thu Sep 18 15:21:04 UTC 2025 aarch64 aarch64 aarch64 GNU/Linux
ubuntu@sysprog:~$ uname -r
6.8.0-86-generic
```
Here `aarch64` indicates that we are running on 64-bit ARM processor. Linux kernel version is `6.8.0-85-generic`. Now we are ready to get going

## List of processes
```sh
ubuntu@sysprog:~$ ps
    PID TTY          TIME CMD
   1810 pts/0    00:00:00 bash
   1821 pts/0    00:00:00 ps
```
Every proces under linux has a 32-bit identifier. It gets its down private virtual memory space. Each process runs a single `thread` by default (unless you create more). To see the list of all processes running on a system:
```sh
ubuntu@sysprog:~$ ps -aef
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 10:13 ?        00:00:01 /usr/lib/systemd/systemd --system --deserialize=24
root           2       0  0 10:13 ?        00:00:00 [kthreadd]
root           3       2  0 10:13 ?        00:00:00 [pool_workqueue_release]
root           4       2  0 10:13 ?        00:00:00 [kworker/R-rcu_g]
root           5       2  0 10:13 ?        00:00:00 [kworker/R-rcu_p]
root           6       2  0 10:13 ?        00:00:00 [kworker/R-slub_]
root           7       2  0 10:13 ?        00:00:00 [kworker/R-netns]
root          10       2  0 10:13 ?        00:00:00 [kworker/0:0H-events_highpri]
root          12       2  0 10:13 ?        00:00:00 [kworker/R-mm_pe]
root          13       2  0 10:13 ?        00:00:00 [rcu_tasks_kthread]
root          14       2  0 10:13 ?        00:00:00 [rcu_tasks_rude_kthread]
root          15       2  0 10:13 ?        00:00:00 [rcu_tasks_trace_kthread]
root          16       2  0 10:13 ?        00:00:00 [ksoftirqd/0]
root          17       2  0 10:13 ?        00:00:00 [rcu_preempt]
root          18       2  0 10:13 ?        00:00:00 [migration/0]
root          19       2  0 10:13 ?        00:00:00 [idle_inject/0]
root          20       2  0 10:13 ?        00:00:00 [cpuhp/0]
root          21       2  0 10:13 ?        00:00:00 [cpuhp/1]
...
```
To see the process listing hierarchically and page the output using `less`
```sh
ubuntu@sysprog:~$ ps -aef --forest | less
....
root        6943       1  0 10:25 ?        00:00:00 sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups
root        7072    6943  0 11:01 ?        00:00:00  \_ sshd: ubuntu [priv]
ubuntu      7127    7072  0 11:01 ?        00:00:00      \_ sshd: ubuntu@pts/0
ubuntu      7128    7127  0 11:01 pts/0    00:00:00          \_ -bash
ubuntu      7141    7128  0 11:02 pts/0    00:00:00              \_ ps -aef --forest
root        6944       1  0 10:25 ?        00:00:00 /sbin/multipathd -d -s
root        6949       1  0 10:25 ?        00:00:00 /usr/libexec/udisks2/udisksd
root        6972       1  0 10:25 ?        00:00:00 /usr/sbin/ModemManager
syslog      6974       1  0 10:25 ?        00:00:00 /usr/sbin/rsyslogd -n -iNONE
```
To get the current `shell` process `PID`
```sh
ubuntu@sysprog:~$ echo $$
7128
```
Lets examine the shell process
```sh
ubuntu@sysprog:~$ ls -l /proc/7128
total 0
dr-xr-xr-x  2 ubuntu ubuntu 0 Oct 20 11:04 attr
-rw-r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 autogroup
-r--------  1 ubuntu ubuntu 0 Oct 20 11:04 auxv
-r--r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 cgroup
--w-------  1 ubuntu ubuntu 0 Oct 20 11:04 clear_refs
-r--r--r--  1 ubuntu ubuntu 0 Oct 20 11:01 cmdline
-rw-r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 comm
-rw-r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 coredump_filter
-r--r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 cpuset
lrwxrwxrwx  1 ubuntu ubuntu 0 Oct 20 11:04 cwd -> /home/ubuntu
-r--------  1 ubuntu ubuntu 0 Oct 20 11:01 environ
lrwxrwxrwx  1 ubuntu ubuntu 0 Oct 20 11:04 exe -> /usr/bin/bash
dr-x------  2 ubuntu ubuntu 4 Oct 20 11:04 fd
....
dr-xr-xr-x  3 ubuntu ubuntu 0 Oct 20 11:04 task
-rw-r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 timens_offsets
-r--r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 timers
-rw-rw-rw-  1 ubuntu ubuntu 0 Oct 20 11:04 timerslack_ns
-rw-r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 uid_map
-r--r--r--  1 ubuntu ubuntu 0 Oct 20 11:04 wchan
```
What just happened? We actually ran `ls`. Linux supports a *virtal* filesystem called `proc` that allows us to visualize various system resources for processes using filestem abstraction. To see the list of open files for a process:
```sh
ubuntu@sysprog:~$ ls -l /proc/7128/fd
total 0
lrwx------ 1 ubuntu ubuntu 64 Oct 20 11:06 0 -> /dev/pts/0
lrwx------ 1 ubuntu ubuntu 64 Oct 20 11:06 1 -> /dev/pts/0
lrwx------ 1 ubuntu ubuntu 64 Oct 20 11:06 2 -> /dev/pts/0
lrwx------ 1 ubuntu ubuntu 64 Oct 20 11:06 255 -> /dev/pts/0
```
If you remember your OS course, 0, 1 & 2 are file descriptors for input, output
and standard-err (`stdin`, `stdout`, `stderr`). `/dev/pts/0` means that they
are all redirected to interactive `pesudo terminal` 0 where we are running the
shell interactively.

```sh
ubuntu@sysprog:~$ tty
/dev/pts/0
```

Few more interesting bits

```sh
ubuntu@sysprog:~$ file /proc/7128/exe
/proc/7128/exe: symbolic link to /usr/bin/bash
ubuntu@sysprog:~$ cat /proc/$$/status
Name:	bash
Umask:	0002
State:	S (sleeping)
Tgid:	7128
Ngid:	0
Pid:	7128
PPid:	7127
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	4 24 27 30 104 1000
NStgid:	7128
NSpid:	7128
NSpgid:	7128
NSsid:	7128
...
```
Keep exploring. This is something that will teach you more than I ever can!

## Linux top command
`top` is one of the most useful commands that you commonly use to look inside
the system performance. To run it non-interactively:

```sh
ubuntu@sysprog:~$ top -b -n 1 -H -c
top - 11:14:11 up  1:00,  2 users,  load average: 0.00, 0.00, 0.00
Threads: 138 total,   1 running, 137 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  1.3 sy,  0.0 ni, 98.7 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
MiB Mem :   3901.7 total,   2570.5 free,    324.0 used,   1175.0 buff/cache
MiB Swap:      0.0 total,      0.0 free,      0.0 used.   3577.7 avail Mem

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
   7220 ubuntu    20   0   12208   4992   2944 R   5.6   0.1   0:00.02 top -b -n 1 -H -c
      1 root      20   0   22440  12800   8832 S   0.0   0.3   0:01.91 /usr/lib/systemd/systemd --system --deserialize=24
      2 root      20   0       0      0      0 S   0.0   0.0   0:00.00 [kthreadd]
      3 root      20   0       0      0      0 S   0.0   0.0   0:00.00 [pool_workqueue_release]
      4 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 [kworker/R-rcu_g]
      5 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 [kworker/R-rcu_p]
      6 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 [kworker/R-slub_]
      7 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 [kworker/R-netns]
     10 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 [kworker/0:0H-events_highpri]
     12 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 [kworker/R-mm_pe]
     13 root      20   0       0      0      0 I   0.0   0.0   0:00.00 [rcu_tasks_kthread]
     14 root      20   0       0      0      0 I   0.0   0.0   0:00.00 [rcu_tasks_rude_kthread]
     15 root      20   0       0      0      0 I   0.0   0.0   0:00.00 [rcu_tasks_trace_kthread]
     16 root      20   0       0      0      0 S   0.0   0.0   0:00.04 [ksoftirqd/0]
     17 root      20   0       0      0      0 I   0.0   0.0   0:00.15 [rcu_preempt]
     18 root      rt   0       0      0      0 S   0.0   0.0   0:00.04 [migration/0]
     19 root     -51   0       0      0      0 S   0.0   0.0   0:00.00 [idle_inject/0]
     20 root      20   0       0      0      0 S   0.0   0.0   0:00.00 [cpuhp/0]
     21 root      20   0       0      0      0 S   0.0   0.0   0:00.00 [cpuhp/1]
     22 root     -51   0       0      0      0 S   0.0   0.0   0:00.00 [idle_inject/1]
...
```

To see the list of threads for a process:

```sh
ubuntu@sysprog:~$ ps -T $$
    PID    SPID TTY      STAT   TIME COMMAND
   1029    1029 pts/0    Ss     0:00 -bash
```

Clearly, the shell proces has just one thread. `SPID` column indicates the
thread-id which is same for the *main* thread within the process. For another
process, I found this is the output:

```sh
ubuntu@sysprog:~$ ps -T 752
    PID    SPID TTY      STAT   TIME COMMAND
    752     752 ?        Ssl    0:00 /usr/bin/python3 /usr/share/unattended-upgrades/unattended-upgrade-shutdown --wait-for-signal
    752     784 ?        Ssl    0:00 /usr/bin/python3 /usr/share/unattended-upgrades/unattended-upgrade-shutdown --wait-for-signal
```

The process has two threads. In order to understand columns like `STAT`, see
`man ps`. *man* is short for manual page.

### Resource information with top

```sh
ubuntu@sysprog:~$ top -H -c -n 1| head

top - 12:30:30 up  1:11,  2 users,  load average: 0.00, 0.00, 0.00
Threads: 146 total,   1 running, 145 sleeping,   0 stopped,   0 zombie
%Cpu0  :  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
%Cpu1  :  6.2 us,  0.0 sy,  0.0 ni, 93.8 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
%Cpu2  :  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
%Cpu3  :  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
MiB Mem :   3901.8 total,   3364.7 free,    288.6 used,    392.1 buff/cache
MiB Swap:      0.0 total,      0.0 free,      0.0 used.   3613.2 avail Mem
```

Legend:

```
us : time running un-niced user processes
sy : time running kernel processes
ni : time running niced user processes
id : time spent in the kernel idle handler
wa : time waiting for I/O completion
hi : time spent servicing hardware interrupts
si : time spent servicing software interrupts
st : time stolen from this vm by the hypervisor
```

## Process Memory Map (Virtual Memory Layout)

`proc` filesystem allows you to look deeper into process memory layout:

```
ubuntu@sysprog:~$ sudo cat /proc/$$/maps
c94a93f30000-c94a94094000 r-xp 00000000 08:01 1802                       /usr/bin/bash
c94a940ab000-c94a940b0000 r--p 0016b000 08:01 1802                       /usr/bin/bash
c94a940b0000-c94a940b9000 rw-p 00170000 08:01 1802                       /usr/bin/bash
c94a940b9000-c94a940c4000 rw-p 00000000 00:00 0
c94ac05fc000-c94ac07a9000 rw-p 00000000 00:00 0                          [heap]
c94a93f30000-c94a94094000 r-xp 00000000 08:01 1802                       /usr/bin/bash
c94a940ab000-c94a940b0000 r--p 0016b000 08:01 1802                       /usr/bin/bash
c94a940b0000-c94a940b9000 rw-p 00170000 08:01 1802                       /usr/bin/bash
c94a940b9000-c94a940c4000 rw-p 00000000 00:00 0
fbcb913a7000-fbcb91400000 r--p 00000000 08:01 7674                       /usr/lib/locale/C.utf8/LC_CTYPE
fbcb91400000-fbcb916eb000 r--p 00000000 08:01 7668                       /usr/lib/locale/locale-archive
fbcb91700000-fbcb91899000 r-xp 00000000 08:01 6282                       /usr/lib/aarch64-linux-gnu/libc.so.6
fbcb91899000-fbcb918ad000 ---p 00199000 08:01 6282                       /usr/lib/aarch64-linux-gnu/libc.so.6
fbcb918ad000-fbcb918b0000 r--p 0019d000 08:01 6282                       /usr/lib/aarch64-linux-gnu/libc.so.6
fbcb918b0000-fbcb918b2000 rw-p 001a0000 08:01 6282                       /usr/lib/aarch64-linux-gnu/libc.so.6
fbcb918b2000-fbcb918be000 rw-p 00000000 00:00 0
fbcb918c0000-fbcb918ef000 r-xp 00000000 08:01 6057                       /usr/lib/aarch64-linux-gnu/libtinfo.so.6.4
fbcb918ef000-fbcb918fc000 ---p 0002f000 08:01 6057                       /usr/lib/aarch64-linux-gnu/libtinfo.so.6.4
fbcb918fc000-fbcb91900000 r--p 0003c000 08:01 6057                       /usr/lib/aarch64-linux-gnu/libtinfo.so.6.4
fbcb91900000-fbcb91901000 rw-p 00040000 08:01 6057                       /usr/lib/aarch64-linux-gnu/libtinfo.so.6.4
fbcb9190e000-fbcb9190f000 r--p 00000000 08:01 7679                       /usr/lib/locale/C.utf8/LC_NUMERIC
fbcb9190f000-fbcb91910000 r--p 00000000 08:01 7682                       /usr/lib/locale/C.utf8/LC_TIME
fbcb91910000-fbcb91937000 r-xp 00000000 08:01 6279                       /usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1
fbcb91937000-fbcb91938000 r--p 00000000 08:01 7673                       /usr/lib/locale/C.utf8/LC_COLLATE
fbcb91938000-fbcb91939000 r--p 00000000 08:01 7677                       /usr/lib/locale/C.utf8/LC_MONETARY
fbcb91939000-fbcb9193a000 r--p 00000000 08:01 7671                       /usr/lib/locale/C.utf8/LC_MESSAGES/SYS_LC_MESSAGES
fbcb9193a000-fbcb91941000 r--s 00000000 08:01 5190                       /usr/lib/aarch64-linux-gnu/gconv/gconv-modules.cache
fbcb91941000-fbcb91943000 rw-p 00000000 00:00 0
fbcb91943000-fbcb91944000 r--p 00000000 08:01 7680                       /usr/lib/locale/C.utf8/LC_PAPER
fbcb91944000-fbcb91945000 r--p 00000000 08:01 7678                       /usr/lib/locale/C.utf8/LC_NAME
fbcb91945000-fbcb91946000 r--p 00000000 08:01 7672                       /usr/lib/locale/C.utf8/LC_ADDRESS
fbcb91946000-fbcb91947000 r--p 00000000 08:01 7681                       /usr/lib/locale/C.utf8/LC_TELEPHONE
fbcb91947000-fbcb91948000 r--p 00000000 08:01 7676                       /usr/lib/locale/C.utf8/LC_MEASUREMENT
fbcb91948000-fbcb91949000 r--p 00000000 08:01 7675                       /usr/lib/locale/C.utf8/LC_IDENTIFICATION
fbcb91949000-fbcb9194b000 rw-p 00000000 00:00 0
fbcb9194b000-fbcb9194d000 r--p 00000000 00:00 0                          [vvar]
fbcb9194d000-fbcb9194e000 r-xp 00000000 00:00 0                          [vdso]
fbcb9194e000-fbcb91950000 r--p 0002e000 08:01 6279                       /usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1
fbcb91950000-fbcb91952000 rw-p 00030000 08:01 6279                       /usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1
fffff1931000-fffff1952000 rw-p 00000000 00:00 0                          [stack]
```

### First three lines

```
address range             perms offset    dev  inode                      pathname
----------------------------------------------------------------------------------
c94a93f30000-c94a94094000 r-xp  00000000 08:01 1802                       /usr/bin/bash
c94a940ab000-c94a940b0000 r--p  0016b000 08:01 1802                       /usr/bin/bash
c94a940b0000-c94a940b9000 rw-p  00170000 08:01 1802                       /usr/bin/bash
```

- address - range of addresses mapped
- perms - permission bits - r(read), w(write), x(execute), p(private), s(shared)

First line has `x` bit set. So it maps to the `text` (or code) segment of
`bash`. Second has `r` and `p` bits set. So its readonly process private data -
`.rodata` segment. and the last line has `rw` and `p` set. So it represents
`.bss` (global uninitialized variables) and `.data` (global initialized
variables) sections of the executable.

You can find more information at [proc
filesystem](https://www.kernel.org/doc/html/latest/filesystems/proc.html). Few
interesting things to explore on your own are `[heap]`, `[stack`], `[vdso]`,
`[vvar]`. You can explore these on your own! (When you do lab!)

## References
1. [Executable and Linkable Format (ELF)](https://refspecs.linuxbase.org/elf/elfspec.pdf)
2. [System V Application Binary Interface (ABI)](https://refspecs.linuxbase.org/elf/x86_64-SysV-psABI.pdf)
3. [Linux /proc filesystem](https://github.com/torvalds/linux/tree/master/fs/proc)
