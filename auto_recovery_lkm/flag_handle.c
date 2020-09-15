#include "flag_handle.h"

void print_flags(int flags)
{
    /* I used this function to test or debug */

    if (flags & O_ACCMODE)
        printk("[O_ACCMODE]");
    if (flags & O_APPEND)
        printk("[O_APPEND]");
    if (flags & O_CLOEXEC)
        printk("[O_CLOEXEC]");
    if (flags & O_CREAT)
        printk("[O_CREAT]");
    if (flags & O_DIRECTORY)
        printk("[O_DIRECTORY]");
    if (flags & O_DIRECT)
        printk("[O_DIRECT]");
    if (flags & O_DSYNC)
        printk("[O_DSYNC]");
    if (flags & O_EXCL)
        printk("[O_EXCL]");
    if (flags & O_LARGEFILE)
        printk("[O_LARGEFILE]");
    if (flags & O_NOCTTY)
        printk("[O_NOCTTY]");
    if (flags & O_NOFOLLOW)
        printk("[O_NOFOLLOW]");
    if (flags & O_NOATIME)
        printk("[O_NOATIME]");
    if (flags & O_NONBLOCK)
        printk("[O_NONBLOCK]");
    if (flags & O_NDELAY)
        printk("[O_NDELAY]");
    if (flags & O_PATH)
        printk("[O_PATH]");
    if (flags & O_RDONLY)
        printk("[O_RDONLY]");
    if (flags & O_RDWR)
        printk("[O_RDWR]");
    if (flags & O_SYNC)
        printk("[O_SYNC]");
    if (flags & O_TMPFILE)
        printk("[O_TMPFILE]");
    if (flags & O_TRUNC)
        printk("[O_TRUNC]");
    if (flags & O_WRONLY)
        printk("[O_WRONLY]");
    if (!flags)
        printk("[NULL]");
    printk("\n");
}

void print_open_status(char *file_path, int flags)
{
    struct kstat st;
    mm_segment_t oldfs = get_fs();
    struct cred *old_cred;
    struct file *fp = filp_open(file_path, O_RDONLY, 0);

    memset(&st, 0, sizeof(st));
    vfs_stat(file_path, &st);

    printk("------------------------------------------------------------\n");
    printk("inode : %-10d| path : %s\n", (int)st.ino, file_path);
    printk("fsize : %-10d| flag : ", (int)st.size);
    print_flags(flags);

    set_fs(get_ds());
    
    old_cred = (struct cred*)get_current_cred();
    commit_creds(prepare_kernel_cred(0));
    
    if (!IS_ERR(fp))
    {
        printk("backup : %-9s\n", "Possible");
        filp_close(fp, NULL);
    }
    else
    {
        printk("backup : %-9s\n", "Cannot");
    }
    printk("------------------------------------------------------------\n");

    commit_creds(old_cred);
    set_fs(oldfs);
}