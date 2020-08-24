# Automatic Recovery In Linux
Ransomware Response Automatic Recovery Kernel Module

<br/>

### auto_recovery_lkm

```bash
# Start Module
$ git clone https://github.com/devgunho/Automatic_Recovery_In_Linux.git
$ cd auto_recovery_lkm
$ make
$ make start

# Remove Module
$ make remove
```

<br/>

<br/>

<br/>

### Materials for project implementation

- [Message logging with printk](#Message-logging-with-printk)
- [Watchman](#Watchman)

<br/>

----

<br/>

### Message logging with printk

The available log levels are:

| Name         | String | Alias function                                    |
| ------------ | ------ | ------------------------------------------------- |
| KERN_EMERG   | “0”    | `pr_emerg()`                                      |
| KERN_ALERT   | “1”    | `pr_alert()`                                      |
| KERN_CRIT    | “2”    | `pr_crit()`                                       |
| KERN_ERR     | “3”    | `pr_err()`                                        |
| KERN_WARNING | “4”    | `pr_warn()`                                       |
| KERN_NOTICE  | “5”    | `pr_notice()`                                     |
| KERN_INFO    | “6”    | `pr_info()`                                       |
| KERN_DEBUG   | “7”    | `pr_debug()` and `pr_devel()` if DEBUG is defined |
| KERN_DEFAULT | “”     |                                                   |
| KERN_CONT    | “c”    | `pr_cont()`                                       |

The log level specifies the importance of a message.

The kernel decides whether to show the message immediately (printing it to the current console) depending on its log level and the current *console_loglevel* (a kernel variable).

If the message priority is higher (lower log level value) than the *console_loglevel* the message will be printed to the console.

<br/>

----

<br/>

### Watchman

![image](https://user-images.githubusercontent.com/41619898/91006040-513de780-e613-11ea-92d0-9477d35911ba.png)

> Watchman is an open source and cross-platform file watching service that watches files and records or performs actions when they change.
>
> It is developed by Facebook and runs on Linux, OS X, FreeBSD, and Solaris.

- https://facebook.github.io/watchman/
- https://github.com/facebook/watchman

<br/>

##### Installing Watchman File Watching Service in Linux

```bash
# use the latest stable release
$ git clone https://github.com/facebook/watchman.git -b v4.9.0 --depth 1
$ cd watchman
$ ./autogen.sh

libtoolize: putting auxiliary files in `.'.
libtoolize: linking file `./ltmain.sh'
libtoolize: putting macros in AC_CONFIG_MACRO_DIR, `m4'.
libtoolize: linking file `m4/libtool.m4'
libtoolize: linking file `m4/ltoptions.m4'
libtoolize: linking file `m4/ltsugar.m4'
libtoolize: linking file `m4/ltversion.m4'
libtoolize: linking file `m4/lt~obsolete.m4'
configure.ac:31: installing './compile'
configure.ac:3: installing './config.guess'
configure.ac:3: installing './config.sub'
configure.ac:4: installing './install-sh'
configure.ac:4: installing './missing'
Makefile.am: installing './depcomp'
parallel-tests: installing './test-driver'

$ ./configure

...
Your build configuration:

        CC = gcc
        CPPFLAGS =  -D_REENTRANT -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
        CFLAGS = -g -O2  -Wall -Wextra -Wdeclaration-after-statement -g -gdwarf-2 -fno-omit-frame-pointer
        CXX = g++ -std=c++11
        CXXFLAGS = -g -O2 -Wall -Wextra -g -gdwarf-2 -fno-omit-frame-pointer
        LDFLAGS =
        prefix: /usr/local
        version: 4.9.0
        state directory: /usr/local/var/run/watchman
        
$ sudo yum install python-devel
$ make
$ sudo make install
```

<br/>

```bash
watchman watch ~/src
watchman watch-list
watchman watch-del ~/src

# In My Env.
[devgun-vm@localhost ~]$ watchman watch ~/Workspace/target_dir
{
    "version": "4.9.0",
    "watch": "/home/devgun-vm/Workspace/target_dir",
    "watcher": "inotify"
}

$ cat /usr/local/var/run/watchman/<username>-state/state
$ cat /usr/local/var/run/watchman/<username>-state/log
```

<br/>

##### Uninstalling Watchman Service in Linux

```
$ sudo make uninstall
$ cd '/usr/local/bin' && rm -f watchman 
$ cd '/usr/local/share/doc/watchman-4.9.0 ' && rm -f README.markdown
```