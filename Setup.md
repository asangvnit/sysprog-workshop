# Prerequisites for Systems Programming Workshop

## What you should know?
- Basic Computer Architecture
- Basic Operating System Concepts
- Basic Shell commands
- Basic C++ Programming

## System Requirements 

You need to install Linux on your system if you are not running it already. Of course if you love your Windows/MacOS too much there are other options:

- [VirtualBox](https://virtualbox.org/) - works on Windows & Mac
- [Multipass](https://canonical.com/multipass) - works on Windows & Mac
- WSL (Windows Services for Linux) - works on Windows
- Parallels - works on Mac and is usually an overkill

VirtualBox is more GUI driven and simple to use. Multipass is easier to use and customize. So we will use `multipass` for this workshop. You also need *Docker* for running VS Code [code-server](https://github.com/coder/code-server) inside a browser.  We also need tools like `cmake`, GNU/Clang C++ compiler, GDB etc.

### Install docker

We are assuming that everyone has a relatively modern Linux/MacOS laptop that’s connected to the internet. This workshop involves downloading software from the internet and accessing other machines on the LAN. In order to get started, make sure that you have the latest version of [docker desktop](https://www.docker.com/products/docker-desktop/) installed. Install it and open the terminal window from inside the docker application. Then run following commands to pull the code-server image from the docker hub and make sure that it is successfully installed (On linux/macos you might need to use sudo while running any of the docker commands)

### Installing code-server docker container

```sh
$ docker pull codercom/code-server
$ docker images
REPOSITORY                  TAG         IMAGE ID       CREATED        SIZE
codercom/code-server        latest      efee0826aa2d   3 days ago     745MB
```
Once the image is pulled, we can now create a container based on it and install all the necessary software.

```sh
$ cd ~
$ mkdir -p .config dev
$ docker run --rm -d --name code-server -p 8081:8080 -v dev:/workspace -v .config:/home/coder/.config codercom/code-server
$ docker ps
```

Now you can point your web browser to [http://localhost:8081/](http://localhost:8081/). You will be prompted to enter a password. This can be found by using the following command:
```
docker exec -it code-server cat  /home/coder/.config/code-server/config.yaml
```

Copy the password displayed after `password:` prompt and use it to launch the vscode right inside your browser. From the menu for vscode, search for “Terminal | New Terminal” and run the following commands:

```sh
$ docker exec -it code-server /bin/bash
$ sudo apt update
$ sudo apt install -y apt-file bind9-dnsutils build-essential gdb git cmake iputils-ping valgrind iproute2
```

Now we are almost ready. We just need to install a few extensions. Here is the list:
- C/C++ Extension Pack
- Gerrit
- Git History

Now we can proceed to installing `multipass`.

### Installing multipass on MacOS

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
 multipass was successfully installed!
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

### Installing multipass on Windows

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

### Installing prerequisites inside unbutu instance

Install the necessary tools and make sure they work
```sh
$ sudo apt update
$ sudo apt install -y linux-tools-common linux-tools-generic
$ sudo apt install -y apt-file bind9-dnsutils build-essential gdb git cmake iputils-ping valgrind iproute2
```
I hope I didn’t miss anything. See you soon!
