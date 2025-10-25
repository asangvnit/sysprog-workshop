# Getting ready to use the git & gerrit workflow

You should connect to Gerrit from your `code-server` [container](Setup.md#installing-code-server-docker-container). In order to generate a SSH keypair, run the following command:
 
```sh
$ docker exec -it code-server /bin/bash
coder@3929e2690e0e:~
```

## Git Configuration
Make sire you have done this (replace My Name with your name and email address with the one you used to register with the gerrit server):
```sh
coder@3929e2690e0e:~ git config --global user.name "My name"
coder@3929e2690e0e:~ git config --global user.email myname@example.com
```

## Generate SSH key for yourself

In order to generate a SSH keypair, run the following command:
 
```sh
coder@3929e2690e0e:~$ ssh-keygen -t ed25519
Generating public/private ed25519 key pair.
Enter file in which to save the key (/home/coder/.ssh/id_ed25519):
Created directory '/home/coder/.ssh'.
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in /home/coder/.ssh/id_ed25519
Your public key has been saved in /home/coder/.ssh/id_ed25519.pub
The key fingerprint is:
SHA256:0vVxDOdWKuAHC1rdY11f8xxtD8XOa38PW60IyQBJIAg coder@3929e2690e0e
The key's randomart image is:
+--[ED25519 256]--+
|E.. ... o.o....**|
|.  . . + o.++=o+X|
|      +   +.+.*==|
|       o . o =  +|
|      . S   .   .|
|       . o .   o.|
|          +   o +|
|           . . =o|
|            . o +|
+----[SHA256]-----+
coder@3929e2690e0e:~$ ls -la .ssh
total 16
drwx------ 2 coder coder 4096 Oct 25 10:27 .
drwx------ 1 coder coder 4096 Oct 25 10:27 ..
-rw------- 1 coder coder  411 Oct 25 10:27 id_ed25519
-rw-r--r-- 1 coder coder  100 Oct 25 10:27 id_ed25519.pub
```

Generated ed25519 public/private keypair

```sh
coder@3929e2690e0e:~$ cat ~/.ssh/id_ed25519.pub
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAINOFMhddYcrRQEBd9QK1YYMszq6ZDmju1+CKJRBcEjFi coder@3929e2690e0e
```

## Add the generated SSH key to the Admin account for gerrit

Open following url in web browser, [http://server-ip:8080/login](http://server-ip:8080/login) as *yourself*, go to the settings and in `New SSH key` text box paste the line printed above (public key).  in New SSH Key section and click "Add New SSH Key" button to save it. You are now ready to use gerrit. Just make sure that you have configured your `user.name` and `user.email` settings for `git`. For more details, see [Gerrit Walkthroughts](https://gerrit-review.googlesource.com/Documentation/intro-gerrit-walkthrough.html).

## Cloning a repository

Once the administrator has created a project for you, you can [clone it](http://server-ip:8080/admin/repos/myproject,general) it. Make sure you copy the `SSH` command next to `Clone with commit-hook` as shown in the image below:

<img src="images/gerrit-clone-cmd.png" alt="gerrit clone command" />

```sh
coder@3929e2690e0e:~$ git clone "ssh://asang@server-ip:29418/myproject" && (cd "myproject" && mkdir -p `git rev-parse --git-dir`/hooks/ && curl -Lo `git rev-parse --git-dir`/hooks/commit-msg http://server-ip:8080/tools/hooks/commit-msg && chmod +x `git rev-parse --git-dir`/hooks/commit-msg)

Cloning into 'myproject'...
The authenticity of host '[192.168.88.5]:29418 ([192.168.88.5]:29418)' can't be established.
ED25519 key fingerprint is SHA256:cNiDbUAY8LnKlTYzGcv5VXIKZ8uuXy01xWLBtAQN7C8.
This key is not known by any other names.
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added '[192.168.88.5]:29418' (ED25519) to the list of known hosts.
remote: Counting objects: 8, done
remote: Finding sources: 100% (8/8)
remote: Total 8 (delta 0), reused 6 (delta 0)
Receiving objects: 100% (8/8), 840 bytes | 840.00 KiB/s, done.
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100  3127  100  3127    0     0   502k      0 --:--:-- --:--:-- --:--:--  508k
coder@3929e2690e0e:~$ ls
myproject
coder@3929e2690e0e:~/myproject$ cd myproject
coder@3929e2690e0e:~/myproject$ git log --oneline
coder@3929e2690e0e:~/myproject$ git status
On branch master

No commits yet

nothing to commit (create/copy files and use "git add" to track)
```

## Making the changes and commiting the code

Now is the time to add your first code review using gerrit. For that we must add some files to the repository. Create a hello.cpp as follows:

```cpp
#include <iostream>

int
main()
{
   std::cout << "Hello world\n";
}
```

Add it to git repo

```sh
coder@3929e2690e0e:~/myproject$ nano hello.cpp
coder@3929e2690e0e:~/myproject$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
	hello.cpp

nothing added to commit but untracked files present (use "git add" to track)

coder@3929e2690e0e:~/myproject$ git add hello.cpp
coder@3929e2690e0e:~/myproject$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
	new file:   hello.cpp
```

Now commit the changes. You can use `nano` editor for your commit message. Make sure that first line is short (less than 80 characters) and title of the changes.

```sh
coder@3929e2690e0e:~/myproject$ git commit
[master (root-commit) e890de6] This is a hello world program
 1 file changed, 7 insertions(+)
 create mode 100644 hello.cpp
coder@3929e2690e0e:~/myproject$ git status
On branch master
Your branch is based on 'origin/master', but the upstream is gone.
  (use "git branch --unset-upstream" to fixup)

nothing to commit, working tree clean
coder@3929e2690e0e:~/myproject$ git log
commit a7ac13f45e68fbfb484b01da4b95f1972ca0660e (HEAD -> master)
Author: Asang Dani <asang.dani@gmail.com>
Date:   Sat Oct 25 11:13:57 2025 +0000

    This is a hello world program

    This is a very simple program that illustrates how gerrit code review works

    Change-Id:     Change-Id: I44d10ca6941813426c9f5000c08f08359af178bd
```

## Push the changes

Now you are ready to publish the changes to your teammates.

```sh
coder@3929e2690e0e:~/myproject$ git push origin HEAD:refs/for/master
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 8 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 376 bytes | 376.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
remote: Processing changes: refs: 1, new: 1, done
remote: commit a7ac13f: warning: too many message lines longer than 72 characters; manually wrap lines
remote:
remote: SUCCESS
remote:
remote:   http://192.168.88.5:8080/c/myproject/+/1 This is a hello world program [NEW]
remote:
To ssh://192.168.88.5:29418/myproject
 * [new reference]   HEAD -> refs/for/master
```

## Code Review

The review page appears as follows:

<img src="images/gerrit-review-page.png" alt="gerrit review page" />

Then reviewer adds comments and replies:

<img src="images/gerrit-review-page-with-comments.png" alt="gerrit review comments" />

### Responding to comments

[![asciicast](https://asciinema.org/a/kQhEnunkZpaetPg3RrLnBVoGy.svg)](https://asciinema.org/a/kQhEnunkZpaetPg3RrLnBVoGy)

Remaining steps must be done in the browser by [marking the comments as Done](images/gerrit-review-reply.png) and hitting [Reply](images/gerrit-review-reply-2.png).

Reviewer sees that all comments are resolved and [replies with +2](images/gerrit-reviewer-ok-to-submit.png).

Submitter refreshes his view and [sees](submitter-ready-to-submit.png) that the status has changed from `Active` to `Ready to submit` and `Submit requirements` are green.

Administrator decides that he is statisfied and clicks `Submit` button to [merge the changes](images/administrator-merges-changes.png) to the `master` branch. After this status of the review changes to `Merged`. Now everyone can *see* the changes when the pull the latest version from the server.

## References

- [Gerrit workflow](https://gerrit-review.googlesource.com/Documentation/intro-gerrit-walkthrough.html)
