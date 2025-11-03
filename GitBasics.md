<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [What is git and why is it required?](#what-is-git-and-why-is-it-required)
- [How do you get started](#how-do-you-get-started)
  - [Step 1 - Basic configuration](#step-1---basic-configuration)
  - [Step 2 - Setting up the repository](#step-2---setting-up-the-repository)
  - [Step 3 - Cloning the repository and working with it](#step-3---cloning-the-repository-and-working-with-it)
  - [Step 4 - Collaborating with others - conflicts and rebasing](#step-4---collaborating-with-others---conflicts-and-rebasing)
- [Important Git Commands](#important-git-commands)
- [Branching and Merging](#branching-and-merging)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## What is git and why is it required?

Scalable distributed version control system (VCS) that's most widely used and well supported. When you develop software, you need to able to track changes to it and be able to continue to develop it while being able to release working versions to your customers. Version control system allows you to do that. [Git](https://git-scm.com/) is also used by Linux kernel. Being distributed means that you have a complete copy the *repository* on your machine thereby allowing you to look at the history, commit changes locally and synchronize with others when you are ready.

## How do you get started

These steps should be done inside `code-server` container. So the first step is to enter the container using `docker exec` CLI as follows:

```console
$ docker exec -it code-server bash
coder@3929e2690e0e:~
```

### Step 1 - Basic configuration

Git is preinstalled on almost all Linux systems. Git clients are also available for Windows and MacOS. There are some one-line configuration steps you need to do before working with git on your system

[![asciicast](https://asciinema.org/a/aqguNuYKYZ95f97IInF6vzbos.svg)](https://asciinema.org/a/aqguNuYKYZ95f97IInF6vzbos)

```console
$ git config --global user.name 'Asang Dani'
$ git config --global user.email asang.dani@gmail.com
$ git config --global --list
user.name=Asang Dani
user.email=asang.dani@gmail.com
```

### Step 2 - Setting up the repository

Second step is to setup a git repository i.e. the *master copy*. Here is how:

[![asciicast](https://asciinema.org/a/0x8A4o7VPxrFxj0whwVj5X24o.svg)](https://asciinema.org/a/0x8A4o7VPxrFxj0whwVj5X24o)

```console
$ mkdir gitrepo
$ cd gitrepo
$ ls
$ git init --bare
hint: Using 'master' as the name for the initial branch. This default branch name
hint: is subject to change. To configure the initial branch name to use in all
hint: of your new repositories, which will suppress this warning, call:
hint:
hint: 	git config --global init.defaultBranch <name>
hint:
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint:
hint: 	git branch -m <name>
Initialized empty Git repository in /home/coder/gitrepo/
$ ls
branches  config  description  HEAD  hooks  info  objects  refs
$
```
### Step 3 - Cloning the repository and working with it

Now that the repository is setup, you need to *clone* it. This is the working copy of the repository on your system where all your commit as first submitted. Periodically, you can *push* the changes to the master repository - also pulling from it to get the changes other teammates are making.

[![asciicast](https://asciinema.org/a/KK9P6tChHWpd2Y1wbowlojCRe.svg)](https://asciinema.org/a/KK9P6tChHWpd2Y1wbowlojCRe)

```console
$ git clone ~/gitrepo clone1
Cloning into 'clone1'...
warning: You appear to have cloned an empty repository.
done.
$ cd clone1
$ # Create a file with one line of text in `nano` editor and save it
$ nano file1.txt
$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
	file1.txt

nothing added to commit but untracked files present (use "git add" to track)
$ git add file1.txt
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
	new file:   file1.txt
$ git commit
[master (root-commit) 0c0e9a8] This is my very first commit. I shouldn't be scared by I am!
 1 file changed, 2 insertions(+)
 create mode 100644 file1.txt
$ git status
On branch master
Your branch is based on 'origin/master', but the upstream is gone.
  (use "git branch --unset-upstream" to fixup)

nothing to commit, working tree clean
$ git log
commit 0c0e9a85e80c8eab30e2eb41adaaa626c5a38450 (HEAD -> master)
Author: Asang Dani <asang.dani@gmail.com>
Date:   Sat Oct 25 15:20:09 2025 +0000

    This is my very first commit. I shouldn't be scared by I am!
$ git push -u origin master
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 8 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 297 bytes | 297.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
To /home/coder/gitrepo
 * [new branch]      master -> master
branch 'master' set up to track 'origin/master'.
$ git log
commit 0c0e9a85e80c8eab30e2eb41adaaa626c5a38450 (HEAD -> master, origin/master)
Author: Asang Dani <asang.dani@gmail.com>
Date:   Sat Oct 25 15:20:09 2025 +0000

    This is my very first commit. I shouldn't be scared by I am!
$ git log --oneline
0c0e9a8 (HEAD -> master, origin/master) This is my very first commit. I shouldn't be scared by I am!
$
```

### Step 4 - Collaborating with others - conflicts and rebasing

One of the main benefits of using a VCS is to be able to collaborate with others effectively and get the work done efficiently and reliably. There are several ways in which you can do that. Following example shows how two users who edit the same file can update the respository after resolving the conflicts. 

[![asciicast](https://asciinema.org/a/SIIKkqfOtpyBslMHyyz4XWmx3.svg)](https://asciinema.org/a/SIIKkqfOtpyBslMHyyz4XWmx3)

## Important Git Commands

Git history view git branches and short commit hashes

```console
$ git log --graph --oneline --decorate --all
```

Pull git changes from upstream and rebase them

```console
$ git pull origin main -r
```

Create a new topic branch and check it out

```console
$ git checkout -b mytopic
```

Push changes upstream for a local branch while setting the upstream tracking

```console
$ git push -u origin mytopic 
```

Show local branches

```console
$ git branch -l
```

Merge changes from main into *mytopic* branch (when currently *mytopic* branch is checked out)

```console
$ git rebase main
$ git rebase main mytopic
```

Display detailed log messages for each commit in patch mode with statistics about the changes

```console
$ git log -p --stat
```
## Branching and Merging

- [Basics of branching and merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging#_basic_merging)
- [Rebase workflow](https://git-scm.com/book/en/v2/Git-Branching-Rebasing)
