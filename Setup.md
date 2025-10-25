## What you should know?
- Basic Computer Architecture
- Basic Operating System Concepts
- Basic Shell commands
- Basic C++ Programming

## System Requirements 
- Laptop with Linux / MacOS installed
- *Docker* for running VS Code [code-server](https://github.com/coder/code-server) inside a browser.
- For Windows Laptops, Having *Ubuntu* [multipass](https://documentation.ubuntu.com/multipass/latest/).
- We need VS Code, CMake, GNU/Clang C++ compiler, GDB and other usual *NIX utilities in order to run and debug the code

We are assuming that everyone has a relatively modern Linux/MacOS laptop that’s connected to the internet. This workshop involves downloading software from the internet and accessing other machines on the LAN. In order to get started, make sure that you have the latest version of [docker desktop](https://www.docker.com/products/docker-desktop/) installed. Install it and open the terminal window from inside the docker application. Then run following commands to pull the code-server image from the docker hub and make sure that it is successfully installed (On linux/macos you might need to use sudo while running any of the docker commands)

## Installing code-server and other tools
```sh
$ sudo docker pull codercom/code-server
$ docker images
REPOSITORY                  TAG         IMAGE ID       CREATED        SIZE
codercom/code-server        latest      efee0826aa2d   3 days ago     745MB
```
Once the image is pulled, we can now create a container based on it and install all the necessary software.

```sh
$ cd ~
$ mkdir -p .config dev
$ docker run --rm -d --name code-server -p 8081:8080 -v $PWD/dev:/workspace -v $PWD/.config:/home/coder/.config codercom/code-server
$ docker ps
```

Now you can point your web browser to [http://localhost:8081/](http://localhost:8081/). You will be prompted to enter a password. This can be found by using the following command:
```
sudo docker exec -it code-server cat  /home/coder/.config/code-server/config.yaml | grep password:
```

Copy the password displayed after password: prompt and use it to launch the vscode right inside your browser. From the menu for vscode, search for “Terminal | New Terminal” and run the following commands:

```sh
$ sudo docker exec -it code-server /bin/bash
$ sudo apt update
$ sudo apt install -y apt-file bind9-dnsutils build-essential gdb git cmake iputils-ping valgrind iproute2
```

Now we are almost ready. We just need to install a few extensions. Here is the list:
- C/C++ Extension Pack
- Gerrit
- Git History

I hope I didn’t miss anything. See you soon!
