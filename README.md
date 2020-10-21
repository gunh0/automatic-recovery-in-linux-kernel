# Automatic Recovery In Linux
Ransomware Response Automatic Recovery Kernel Module

![LKM (EN)](README.assets/LKM (EN).jpg)

<br/>

<br/>

### # My Env.

**VirtualBox 6.1.12 r139181**

**CentOS Linux release 7.8.2003 (Core)**

<br/>

<br/>

### # auto_recovery_lkm Install

```bash
# Start Module
$ git clone https://github.com/devgunho/Automatic_Recovery_In_Linux.git
$ sudo su
# cd Automatic_Recovery_In_Linux
# cd auto_recovery_lkm
auto_recovery_lkm]# make
auto_recovery_lkm]# make start

# Only files that exist in the target directory will automatically be backed up when an open action occurs.
# Recovery cannot proceed simultaneously while backup is taking place.

# Remove Module
auto_recovery_lkm]# make rmmod

# Target, Backup directory permisson change
# [localhost /]$ sudo chmod -R 777 target_dir/
# [localhost /]$ sudo chmod -R 777 backup_dir/
# to do this command
auto_recovery_lkm]# make auth
```

```bash
# Delete All
auto_recovery_lkm]# make remove
auto_recovery_lkm]# make clean
```

<br/>

### # lkmautobackup-recovery

```bash
# Stop lkm
auto_recovery_lkm]# make rmmod

# move to lkmautobackup-recovery directory
lkmautobackup-recovery]# make
lkmautobackup-recovery]# make start
# and check /recovery_dir
```

<br/>

### # Validation

```shell
$ sha1sum 'target file'

# Example
# Before
[root@localhost target_dir]# xxd abc.txt
0000000: 6464 6464 0a0a                           dddd..
[root@localhost target_dir]# sha1sum abc.txt
c393fbd14d89dd594f41ab2cd9023b841a42894f  abc.txt

# After
[root@localhost recovery_dir]# xxd abc.txt
0000000: 6464 6464 0a0a                           dddd..
[root@localhost recovery_dir]# sha1sum abc.txt
c393fbd14d89dd594f41ab2cd9023b841a42894f  abc.txt
```

<br/>

### # Details

The Linux kernel contains a Virtual File System layer which is used during system calls acting on files.

The VFS is an indirection layer which handles the file oriented system calls and calls the necessary functions in the physical filesystem code to do the I/O.

When a process issues a file oriented system call, the kernel calls a function contained in the VFS.

This function handles the structure independent manipulations and redirects the call to a function contained in the physical filesystem code, which is responsible for handling the structure dependent operations.

Filesystem code uses the buffer cache functions to request I/O on devices.

**This scheme is illustrated in this figure:**

![image](https://user-images.githubusercontent.com/41619898/91268608-9a776e00-e7b0-11ea-8178-079c05e75d51.png)

<br/>

#### **VFS Key Objects**

![image](https://user-images.githubusercontent.com/41619898/91269796-a6642f80-e7b2-11ea-8c6c-6229fea5c990.png)

<br/>

- **inode object**

​	Linux manages all objects in the file system through objects called inodes (index nodes).

​	Inodes refer to symbolic links or directories or files that link to other objects.

- **dentry object**

​	The hierarchical nature of the file system is managed by another object called the dentry object.

​	There is one root dentry referenced in the superblock in the file system, which is the only dentry without a parent layer.

- **file object**

  A file object exists in each open file on a Linux system.

  This object contains information specific to the open instance of that user.

<br/>

#### **VFS Key Objects**

![image](https://user-images.githubusercontent.com/41619898/91270360-79fce300-e7b3-11ea-9e3e-3972b28b2944.png)

Major objects dynamically managed by VFS include **dentry** and **inode** objects.

This object is cached to improve access to the underlying file system.

When the file is opened, the dentry cache is populated with entries that represent the directory level that represents the path.

An inode is also created for the object representing the file.

A dentry cache is created using a hash table and is hashed with the name of the object.

The inode cache is implemented with a hash table and two lists needed to find quickly.

The first list defines which inodes are currently in use, and the second list defines which inodes are not used.

Inodes in use are also stored in hash tables.

<br/>

### Erebus Ransomware Affected File Types

```
.1cd, .3dm, .3ds, .3fr, .3g2, .3gp, .3pr, .7z, .7zip, .aac, .ab4, .abd, .accdb, .accde, .accdr, .accdt, .ach, .acr, .act, .adb, .adp, .ads, .agdl, .ai,
.aiff, .ait, .al, .aoi, .apj, .arw, .ascx, .asf, .asm, .asp, .aspx, .asx, .atb, .avi, .awg, .back, .backup, .backupdb, .bak, .bank, .bay, .bdb, .bgt, .bik,
.bin, .bkp, .blend, .bmp, .bpw, .c, .cdb, .cdf, .cdr, .cdr3, .cdr4, .cdr5, .cdr6, .cdrw, .cdx, .ce1, .ce2, .cer, .cfg, .cfn, .cgm, .cib, .class, .cls, .cmt,
.config, .contact, .cpi, .cpp, .cr2, .craw, .crt, .crw, .cs, .csh, .csl, .css, .csv, .dac, .dat, .db, .db_journal, .db3, .dbf, .dbx, .dc2, .dcr, .dcs, .ddd,
.ddoc, .ddrw, .dds, .def, .der, .des, .design, .dgc, .dit, .djvu, .dng, .doc, .docm, .docx, .dot, .dotm, .dotx, .drf, .drw, .dtd, .dwg, .dxb, .dxf, .dxg,
.edb, .eml, .eps, .erbsql, .erf, .exf, .fdb, .ffd, .fff, .fh, .fhd, .fla, .flac, .flb, .flf, .flv, .flvv, .fpx, .fxg, .gif, .gray, .grey, .groups, .gry,
.h, .hbk, .hdd, .hpp, .html, .ibank, .ibd, .ibz, .idx, .iif, .iiq, .incpas, .indd, .info, .info_, .ini, .jar, .java, .jnt, .jpe, .jpeg, .jpg, .js, .json,
.kc2, .kdbx, .kdc, .key, .kpdx, .kwm, .laccdb, .lck, .ldf, .lit, .lock, .log, .lua, .m, .m2ts, .m3u, .m4p, .m4v, .mab, .mapimail, .max, .mbx, .md, .mdb,
.mdc, .mdf, .mef, .mfw, .mid, .mkv, .mlb, .mmw, .mny, .moneywell, .mos, .mov, .mp3, .mp4, .mpeg, .mpg, .mrw, .msf, .msg, .myd, .nd, .ndd, .ndf, .nef,
.nk2, .nop, .nrw, .ns2, .ns3, .ns4, .nsd, .nsf, .nsg, .nsh, .nvram, .nwb, .nx2, .nxl, .nyf, .oab, .obj, .odb, .odc, .odf, .odg, .odm, .odp, .ods, .odt,
.ogg, .oil, .omg, .orf, .ost, .otg, .oth, .otp, .ots, .ott, .p12, .p7b, .p7c, .pab, .pages, .pas, .pat, .pbf, .pcd, .pct, .pdb, .pdd, .pdf, .pef, .pem,
.pfx, .php, .pif, .pl, .plc, .plus_muhd, .pm, .pm!, .pmi, .pmj, .pml, .pmm, .pmo, .pmr, .pnc, .pnd, .png, .pnx, .pot, .potm, .potx, .ppam, .pps, .ppsm,
.ppsm, .ppsx, .ppt, .pptm, .pptm, .pptx, .prf, .ps, .psafe3, .psd, .pspimage, .pst, .ptx, .pwm, .py, .qba, .qbb, .qbm, .qbr, .qbw, .qbx, .qby, .qcow,
.qcow2, .qed, .qtb, .r3d, .raf, .rar, .rat, .raw, .rdb, .rm, .rtf, .rvt, .rw2, .rwl, .rwz, .s3db, .safe, .sas7bdat, .sav, .save, .say, .sd0, .sda, .sdb,
.sdf, .sh, .sldm, .sldx, .sql, .sqlite, .sqlite3, .sqlitedb, .sqlite-shm, .sqlite-wal, .sr2, .srb, .srf, .srs, .srt, .srw, .st4, .st5, .st6, .st7, .st8,
.stc, .std, .sti, .stm, .stw, .stx, .svg, .swf, .sxc, .sxd, .sxg, .sxi, .sxm, .sxw, .tbb, .tbn, .tex, .tga, .thm, .tif, .tlg, .tlx, .txt, .usr, .vbox, .vdi,
.vhd, .vhdx, .vmdk, .vmsd, .vmx, .vmxf, .vob, .wab, .wad, .wallet, .war, .wav, .wb2, .wma, .wmf, .wmv, .wpd, .wps, .x11, .x3f, .xis, .xla, .xlam, .xlk, .xlm,
.xlr, .xls, .xlsb, .xlsm, .xlsx, .xlt, .xltm, .xltx, .xlw, .xml, .ycbcra, .yuv, .zip
```

<br/>

<br/>

### # Materials for project implementation

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