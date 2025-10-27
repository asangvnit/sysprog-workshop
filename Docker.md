# Introduction to docker
- Haven't heard of [docker](https://docker.com/)? Were you sleeping under a rock?
- Official definition is not very useful
 > Docker is an open platform for developing, shipping, and running applications
- Its a platform for developing and deploying applications in *containers*
  - Provides isolation - network, filesystem, resources (CPU, Memory, ...)
  - Sandbox environment that doesn't change
  - Testing in different environments
- *Much more efficient* than full Virtualization. Uses the same kernel as host operating system (on Linux)
  - Containers are ideal for microservices, CI/CD pipelines, and fast-scaling cloud workloads
  - Freezing the *artifacts* or runtime environment
  - Easy to backup and reuse across different hosts
- Easy to use - GUI as well as CLI interface
- Allows controlling CPU/Memory usage for the containers

## Docker Architecture

Docker desktop contains all the basic components to create and run docker images. It supports CLI as well as GUI interface. Following diagram shows the basic components:

<div align="center">
  <img src="images/docker-architecture.png" alt="architecture" width="400">
</div>

`Docker engine` is a background service and that runs on the *host* and runs and manages both the containers and images.

## Getting Started
- Easiest way to use one of existing image on [docker hub](https://hub.docker.com/) as a base image. Thousands of useful base images exist for things like Apache Web Server, MySql Database Server and many more.
- You can build (and publish/upload) your own.
- Many organizations use their internal [docker registries]([https://hub.docker.com/_/registry](https://distribution.github.io/distribution/)) for security and standardization
- Docker can use *host* networking or have its own isolated network
- Local ports can be forwarded to docker containers

## Building your first docker image and a container

### Create an empty index.html file for the apache webserver

```sh
mkdir public-html
touch publich-html/index.html
```

### Create a Dockerfile for your container
Following two lines instruct that we should begin with Apache 2.4 base image and copy contents of subdirectory `public-html` to `/usr/local/apache2/htdocs/` folder within the container
```
FROM httpd:2.4
COPY ./public-html/ /usr/local/apache2/htdocs/
```

### Build the image and start the container

Following line create a new image tagged as  `my-apache2` in `.` i.e. current directory (this is where your `Dockerfile` is).
```sh
$ docker buildx build . -t my-apache2 --progress-plain
```
Once the image is created it should be visible locally
```sh
$ docker images
REPOSITORY                  TAG          IMAGE ID       CREATED          SIZE
my-apache2                  latest       259b85f86f7c   41 seconds ago   117MB
```
Following line starts a container named `my-apache-server` and any requests coming to port `8080` on the `host` will be forwarded to port `80` inside `my-apache-server` container. Option `-d` causes the container to run in the background.  
```
$ docker run -d --name my-apache-server -p 8080:80 my-apache2
cbd21c8d860b2a407e0aad742faa083cded6133abbb5da56f62e2e853dc23ed1
```
The hex value printed is the full container ID. To the list of currently running containers (including the dead ones)
```
$ docker ps -a
CONTAINER ID   IMAGE         COMMAND               CREATED         STATUS                 PORTS                                        NAMES
cbd21c8d860b   my-apache2    "httpd-foreground"    2 minutes ago   Up 2 minutes           0.0.0.0:8080->80/tcp, [::]:8080->80/tcp      my-apache-server
```
You can refer to the container by name or ID. Notice that container ID in above command is truncated. To see the full ID, you can run `dockr ps --no-trunc`. You can stop or delete the container. A stopped container can be restarted by specifying its name or ID using `docker start` command.

### Lets test if the web server is running
```sh
$ wget http://localhost:8080/
--2025-10-19 15:11:11--  http://localhost:8080/
Resolving localhost (localhost)... 127.0.0.1
Connecting to localhost (localhost)|127.0.0.1|:8080... connected.
HTTP request sent, awaiting response... 200 OK
Length: 0 [text/html]
Saving to: ‘index.html’

index.html                            [ <=>                                                          ]       0  --.-KB/s    in 0s

2025-10-19 15:11:11 (0.00 B/s) - ‘index.html’ saved [0/0]
```

### Stopping & removing the container
```sh
$ docker stop my-apache-server
my-apache-server
$ docker ps
(no output)
$ docker ps -a
CONTAINER ID   IMAGE                       COMMAND                  CREATED         STATUS                     PORTS            NAMES
cbd21c8d860b   my-apache2                  "httpd-foreground"       6 minutes ago   Exited (0) 5 seconds ago                    my-apache-server
```
To start the container again,
```sh
$ docker start my-apache-server
my-apache-server
CONTAINER ID   IMAGE                       COMMAND                  CREATED         STATUS                 PORTS                                     NAMES
cbd21c8d860b   my-apache2                  "httpd-foreground"       8 minutes ago   Up 11 seconds          0.0.0.0:8080->80/tcp, [::]:8080->80/tcp   my-apache-server
```
To remove the container (be very careful - there is no going back)
```sh
$ docker rm my-apache-server
Error response from daemon: cannot remove container "my-apache-server": container is running: stop the container before removing or force remove
$ docker stop my-apache-server && docker rm my-apache-server
my-apache-server
my-apache-server
$ docker ps -a
CONTAINER ID   IMAGE                       COMMAND                  CREATED       STATUS                 PORTS           NAMES
```
## For more information
1. [docker CLI reference](https://docs.docker.com/reference/cli/docker/)
2. [docker manuals](https://docs.docker.com/manuals/)
