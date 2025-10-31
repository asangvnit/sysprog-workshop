<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Instructions for setting up gerrit server/container](#instructions-for-setting-up-gerrit-servercontainer)
  - [Install docker on your system](#install-docker-on-your-system)
  - [Create gerrit container from CLI](#create-gerrit-container-from-cli)
  - [Generate SSH key for the admin account](#generate-ssh-key-for-the-admin-account)
  - [Add the generated SSH key to the Admin account for gerrit](#add-the-generated-ssh-key-to-the-admin-account-for-gerrit)
  - [Miscellaneous](#miscellaneous)
  - [References](#references)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Instructions for setting up gerrit server/container

## Install docker on your system

Install docker on the server where you are planning to use gerrit

## Create gerrit container from CLI

Create Gerrit containers as follows (server-ip is the IP address of the linux server on which gerrit container is being installed.

```sh
docker run -d --name gerrit -e CANONICAL_WEB_URL=http://<server-ip>:8080 -p 8080:8080 -p 29418:29418 gerritcodereview/gerrit
```

You can connect to gerrit [here](http://server-ip:8080/login). Click on your username under "Choose:" and you will be automatically logged in. This is a dummy system with no real authentication. Now you need to add your SSH Public Key for gerrit to allow you to pull/push code changes. Here are the steps to generate and save the key.

## Generate SSH key for the admin account

This step is required only if the account you are using to install gerrit on your linux system doesn't have an SSH Key. If it does, you can skip this step. Otherwise run the following command and accept the defauls
 
```sh
$ ssh-keygen -t ed25519
```

This will generate ed 25519 public/private keypair and save it to *~/.ssh* directory in your home directory.

```sh
$ cat $HOME/.ssh/id_ed25519.pub
```

## Add the generated SSH key to the Admin account for gerrit

Open following url in web browser, login as *admin* [http://server-ip:8080/settings/#SSHKeys](http://<server-ip>:8080/settings/#SSHKeys)

in New SSH Key section and click "ADD NEW SSH KEY" button to save it

https://gerrit-review.googlesource.com/Documentation/intro-gerrit-walkthrough.html

## Miscellaneous

To commit code:

1. Clone the repo

2. Make the changes

3. Commit the changes - git commit

5. Push the changes - git push origin HEAD:refs/for/master

## References

- [Gerrit workflow](https://gerrit-review.googlesource.com/Documentation/intro-gerrit-walkthrough.html)
