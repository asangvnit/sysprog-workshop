# Prerequisites for Systems Programming Workshop

## What you should know?

In order to make the most from this seminar, we expect that you have a good background in following areas.

- Basic Computer Architecture
- Basic Operating System Concepts
- Basic Shell commands
- Basic C++ Programming

## System Requirements 

In order to follow along through the theory and lab sessions for this seminar, you will need to install Linux on your laptop/desktop if you are not running it already. In fact even if your laptop is running some flavour or Linux already, we strongly recommend that you follow the steps given in this document. There are many options that we considered for this workshop. Here are some of them:

- [VirtualBox](https://virtualbox.org/) - works on Windows & Mac
- [Multipass](https://canonical.com/multipass) - works on Windows & Mac
- WSL (Windows Services for Linux) - works on Windows
- Parallels - works on Mac and is usually an overkill

VirtualBox is more GUI driven and simple to use. However, Multipass is easier to use and customize and CLI based making it an ideal choice.  We will use `multipass` for this workshop for running performance and leak monitoring tools covered during the theory session of this workshop.

For doing programming assignments in C++, you will need some code editor. [Visual Studio Code](https://code.visualstudio.com/download) is a good choice these days for most of the beginners. To make it easier to install VS Code and accompanying tools, we will use *Docker*. [code-server](https://github.com/coder/code-server) is a popular option for setting up VS Code inside a docker container and then using it directly from your Web Browser (Chrome/Microsoft Edge/Firefox etc). Inside the container, you will also need to install tools like `cmake`, GNU/Clang C++ compiler, GDB etc. So lets get started right away.

## Install docker

Make sure that you download and install the latest version of [docker desktop](https://www.docker.com/products/docker-desktop/) on your system i.e. laptop/desktop (referred to as `host` in the rest of this document). Install it and open the terminal window inside docker destkop. Then run following commands to pull the `code-server` image from the **docker hub**.

### Installing code-server container

Execute following commands inside the terminal windows inside `docker desktop` application


```sh
$ docker pull codercom/code-server
$ docker images
REPOSITORY                  TAG         IMAGE ID       CREATED        SIZE
codercom/code-server        latest      efee0826aa2d   3 days ago     745MB
```

Once the image is pulled, we can now create a container based on it and install the necessary software.

#### On Windows host

```sh
C:\Users\Amar> mkdir config dev
C:\Users\Amar> docker run -d --name code-server -p 8081:8080 -v ./dev:/workspace -v ./config:/home/coder/.config codercom/code-server
783a94d539dbecb76a2a4afb538569cb426296f94dd6b3f98f57f6540cb841ee
C:\Users\Amar> docker ps
CONTAINER ID   IMAGE                         COMMAND                  CREATED         STATUS         PORTS                                                                                          NAMES
783a94d539db   codercom/code-server:latest   "/usr/bin/entrypoint…"   2 seconds ago   Up 2 seconds   0.0.0.0:8081->8080/tcp, [::]:8081->8080/tcp
```

#### On Linux/MacOS host
```sh
$ cd ~
$ mkdir config dev
$ chmod 777 -R config dev
$ sudo docker run -d --name code-server -p 8081:8080 -v ./dev:/workspace -v ./config:/home/coder/.config \
   -u "$(id -u):$(id -g)" -e "DOCKER_USER=$USER" codercom/code-server
783a94d539dbecb76a2a4afb538569cb426296f94dd6b3f98f57f6540cb841ee
$ sudo docker ps
CONTAINER ID   IMAGE                         COMMAND                  CREATED         STATUS         PORTS                                                                                          NAMES
783a94d539db   codercom/code-server:latest   "/usr/bin/entrypoint…"   2 seconds ago   Up 2 seconds   0.0.0.0:8081->8080/tcp, [::]:8081->8080/tcp
```

Now you can point your web browser to [http://localhost:8081/](http://localhost:8081/). You will be prompted to enter a password. This can be found by using the following command:

```
$ docker exec -it code-server cat /home/coder/.config/code-server/config.yaml
```

Copy the password displayed after `password:` prompt and use it to login to VS Code inside your browser. From the menu for VSCode, search for “Terminal | New Terminal” and run the following commands:

```sh
$ sudo apt update
$ sudo apt install -y apt-file bind9-dnsutils build-essential gdb git cmake iputils-ping valgrind iproute2
```

Now we are almost ready. We just need to install a few extensions. Here is the list:

- C/C++ Extension Pack
- Gerrit
- Git History

Now we can proceed to installing `multipass`.

## Installing multipass

The steps to install `multipass` are slightly different for Windows and MacOS. Following sections show you how.

### Installing multipass on MacOS

First, you need to install [HomeBrew](https://brew.sh/)
```sh
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
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
Now you can go to the command prompt and create ubuntu instance. Here, we create an ubuntu instance with 4GB RAM, 10GB diskspace and 4 CPUs. You can choose different parameters based on your system capabilities.

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

[Download](https://canonical.com/multipass/download/windows) multipass for windows and run the installer. During installation, when prompted use Microsoft's [Hyper-V](https://en.wikipedia.org/wiki/Hyper-V) as the [Hypervisor](https://en.wikipedia.org/wiki/Hypervisor). If you have `Windows 10 Home` edition, which doesn't supports Hyper-V, you will need to download and install [VirtualBox](https://virtualbox.org/). So please do that first. Once multipass is installed, you can go to the command prompt and create an ubuntu instance. Open `cmd` window and execute following commands:
```sh
C:\>cd C:\Program Files\Multipass\bin
C:\Program Files\Multipass\bin>multipass version
multipass   1.16.1+win
multipassd  1.16.1+win
```

Create ubuntu instance on Windows following similar steps as explain above.

```sh
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

## Installing prerequisites inside ubuntu instance

Run following command to connect to `sysprog` instance:

```
$ multipass shell sysprog
```

Install the necessary tools and make sure they work.

```sh
$ sudo apt update
$ sudo apt install -y linux-tools-common linux-tools-generic
$ sudo apt install -y apt-file bind9-dnsutils build-essential gdb git cmake iputils-ping valgrind iproute2
```

I hope I didn’t miss anything. See you soon!
