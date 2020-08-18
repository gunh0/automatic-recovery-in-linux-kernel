# Automatic Recovery In Linux
Ransomware Response Automatic Recovery Kernel Module

<br/>

<br/>

### Watchman

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