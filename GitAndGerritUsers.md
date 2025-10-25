# Getting ready to use the git & gerrit workflow

## Generate SSH key for yourself

You should connect to Gerrit from your `code-server` [container](Setup.md#installing-code-server-docker-container). In order to generate a SSH keypair, run the following command:
 
```sh
$ docker exec -it code-server /bin/bash
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


5. Push the changes - git push origin HEAD:refs/for/master

## References

- [Gerrit workflow](https://gerrit-review.googlesource.com/Documentation/intro-gerrit-walkthrough.html)
