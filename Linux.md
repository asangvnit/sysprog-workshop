# Introduction to linux

Most widely used **NIX based operating system in the world today. Has many variants and forks - but `debian`, `ubuntu` and `fedora` are some of the most widely used ones. You can install it on your laptop directly. Of course if you love your Windows/MacOS too much there are other options:

- [VirtualBox](https://virtualbox.org/) - works on Windows & Mac
- [Multipass](https://canonical.com/multipass) - works on Windows & Mac
- WSL (Windows Services for Linux) - works on Windows
- Paralles - works on Mac and is usually an overkill

VirtualBox is more GUI driven and simple to use. Multipass is easier to use and customize

## Installing multipass on MacOS

First, you need to install [HomeBrew](https://brew.sh/)
```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Now we are ready to install multipass.
```sh
$ brew install --cask multipass
==> Downloading https://raw.githubusercontent.com/Homebrew/homebrew-cask/aa0c7e1341889c0992cda0693a043b898fe6b34c/Casks/m/multipass.rb
########################################################################################################################################################################################## 100.0%
==> Downloading https://github.com/canonical/multipass/releases/download/v1.16.1/multipass-1.16.1+mac-Darwin.pkg
==> Downloading from https://release-assets.githubusercontent.com/github-production-release-asset/114128199/0c7f4e9f-b767-409d-805e-37837458bbbc?sp=r&sv=2018-11-09&sr=b&spr=https&se=2025-10-20T
########################################################################################################################################################################################## 100.0%
==> Installing Cask multipass
==> Running installer for multipass with `sudo` (which may request your password)...
Password:
installer: Package name is multipass
installer: Installing at base path /
installer: The install was successful.
🍺  multipass was successfully installed!
```
Now you can go to the command prompt and create ubuntu instance.

### Creating ubuntu instance on MacOS
Here we are creating an Ubuntu instance with 4GB RAM, 10GB diskspace and 4 CPUs. You can choose different parameters based on your host's capabilities.

```sh
$ sudo multipass launch --name sysprog --cpus 4 --memory 4G --disk 10G 24.04
Launched: sysprog
$ sudo multipass list
Name                    State             IPv4             Image
sysprog                 Running           192.168.2.2      Ubuntu 24.04 LTS
```
Now connect to it:
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

## Installing multipass on Windows

[Download](https://canonical.com/multipass/download/windows) multipass for windows and run the installer. During installation, when prompted use Microsoft's [Hyper-V](https://en.wikipedia.org/wiki/Hyper-V) as the [Hypervisor](https://en.wikipedia.org/wiki/Hypervisor). Once installed, you can go to the command prompt and create an ubuntu instance. Open `cmd` window and execute following commands:
```sh
C:\>cd C:\Program Files\Multipass\bin
C:\Program Files\Multipass\bin>multipass version
multipass   1.16.1+win
multipassd  1.16.1+win
C:\Program Files\Multipass\bin>multipass launch --name sysprog --cpus 4 --memory 4G --disk 10G 24.04
Launched: sysprog

C:\Program Files\Multipass\bin>multipass list
Name                    State             IPv4             Image
sysprog                 Running           192.168.115.22   Ubuntu 24.04 LTS
```
Now connect to it:
```sh
C:\Program Files\Multipass\bin>multipass shell sysprog
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
```
Here `aarch64` indicates that we are running on 64-bit ARM processor. Linux kernel version is `6.8.0-85-generic`.

## Installing prerequisites inside Unbutu instance

Install the necessary tools and make sure they work
```sh
$ sudo apt update
$ sudo apt install -y linux-tools-common linux-tools-generic
$ sudo apt install -y apt-file bind9-dnsutils build-essential gdb git cmake iputils-ping valgrind iproute2
```

Now we are ready to get going

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
If you remember your OS course, 0, 1 & 2 are file descriptors for input, output and standard-err (`stdin`, `stdout`, `stderr`). `/dev/pts/0` means that they are all redirected to interactive `pesudo terminal` 0 where we are running the shell interactivately.
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
`top` is one of the most useful commands that you commonly use to look inside the system performance. To run it non interactively:
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
To see the list of threads for a process
```sh
ubuntu@sysprog:~$ ps -T $$
    PID    SPID TTY      STAT   TIME COMMAND
   1029    1029 pts/0    Ss     0:00 -bash
```
Clearly, the shell proces has just one thread. `SPID` column indicates the thread-id which is same for the *main* thread within the process. For another process, I found this is the output:
```sh
ubuntu@sysprog:~$ ps -T 752
    PID    SPID TTY      STAT   TIME COMMAND
    752     752 ?        Ssl    0:00 /usr/bin/python3 /usr/share/unattended-upgrades/unattended-upgrade-shutdown --wait-for-signal
    752     784 ?        Ssl    0:00 /usr/bin/python3 /usr/share/unattended-upgrades/unattended-upgrade-shutdown --wait-for-signal
```
The process has two threads. In order to understand columns like `STAT`, see `man ps`. *man* is short for manual page.
### Resource information with top
``sh
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
