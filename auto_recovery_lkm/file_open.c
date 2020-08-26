#include "file_open.h"

void read_file(char *filename)
{
    //int fd;
    //char buf[1];
    struct file *filp;
    char bufs[100];
    int ret;
 
    /* kernel memory access setting */
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);

    strcpy(bufs, "hello my world");
 
    /* open a file */
    filp = filp_open(filename, O_RDWR, S_IRUSR|S_IWUSR);
    if (IS_ERR(filp)) {
        printk("open error\n");
        return;
    }
    else {
        printk("open success\n");
    }
 
    /* write example */
    printk("filp->f_pos = %d\n", (int)filp->f_pos);
    vfs_write(filp, bufs, strlen(bufs), &filp->f_pos);
    printk("filp->f_pos = %d\n", (int)filp->f_pos);
 
    /* read example */
    printk(KERN_DEBUG);
    filp->f_pos = 3;
    do {
        printk("%d : ", (int)filp->f_pos);
        ret = vfs_read(filp, bufs, 2, &filp->f_pos);
        if (ret != 0) {
            printk("%d : %c%c : ", ret, bufs[0], bufs[1]);
            printk("%d", (int)filp->f_pos);
        }
        printk("\n");
    } while(ret != 0);
 
    filp_close(filp, NULL);  /* filp_close(filp, current->files) ?  */
    /* restore kernel memory setting */
    set_fs(old_fs);
}
