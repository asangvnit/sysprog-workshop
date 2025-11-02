<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Understanding git basics](#understanding-git-basics)
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

### Step 1 - Basic configuration

Git is preinstalled on almost all Linux systems. Git clients are also available for Windows and MacOS. There are some one-line configuration steps you need to do before working with git on your system

[![asciicast](https://asciinema.org/a/aqguNuYKYZ95f97IInF6vzbos.svg)](https://asciinema.org/a/aqguNuYKYZ95f97IInF6vzbos)

### Step 2 - Setting up the repository

Second step is to setup a git repository i.e. the *master copy*. Here is how:

[![asciicast](https://asciinema.org/a/0x8A4o7VPxrFxj0whwVj5X24o.svg)](https://asciinema.org/a/0x8A4o7VPxrFxj0whwVj5X24o)

### Step 3 - Cloning the repository and working with it

Now that the repository is setup, you need to *clone* it. This is the working copy of the repository on your system where all your commit as first submitted. Periodically, you can *push* the changes to the master repository - also pulling from it to get the changes other teammates are making.

[![asciicast](https://asciinema.org/a/KK9P6tChHWpd2Y1wbowlojCRe.svg)](https://asciinema.org/a/KK9P6tChHWpd2Y1wbowlojCRe)

### Step 4 - Collaborating with others - conflicts and rebasing

One of the main benefits of using a VCS is to be able to collaborate with others effectively and get the work done efficiently and reliably. There are several ways in which you can do that. Following example shows how two users who edit the same file can update the respository after resolving the conflicts. 

[![asciicast](https://asciinema.org/a/SIIKkqfOtpyBslMHyyz4XWmx3.svg)](https://asciinema.org/a/SIIKkqfOtpyBslMHyyz4XWmx3)

## Important Git Commands

Show the status of current git clone

```sh
git status
```

Git history view git branches and short commit hashes

```sh
git log --graph --oneline --decorate --all
```

Pull git changes from upstream and rebase them

```sh
git pull origin main -r
```

Create a new topic branch and check it out

```sh
git checkout -b mytopic
```

Push changes upstream for a local branch while setting the upstream tracking

```sh
git push -u origin mytopic 
```

Show local branches

```sh
git branch -l
```

Merge changes from main into *mytopic* branch (when currently *mytopic* branch is checked out)

```sh
git rebase main
git rebase main mytopic
```

Display detailed log messages for each commit in patch mode with statistics about the changes

```sh
git log -p --stat
```
## Branching and Merging

- [Basics of branching and merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging#_basic_merging)
- [Rebase workflow](https://git-scm.com/book/en/v2/Git-Branching-Rebasing)
