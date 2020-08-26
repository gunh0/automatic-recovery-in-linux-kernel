#include "file_open.h"

#define BUF_SIZE 1024

void read_file(char *filename)
{
    struct file *filp;
    unsigned char buf[BUF_SIZE];
    int ret;
    int line_counter=0;
 
    /* kernel memory access setting */
    /* To use file function, unlock the kernel memory permission */
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);
 
    /* open a file */
    filp = filp_open(filename, O_RDWR, S_IRUSR|S_IWUSR);
    if (IS_ERR(filp)) {
        printk("open error : %s\n",filename);
        return;
    }
    else {
        printk("open success : %s\n",filename);
    

        printk("Offset(h) [%s]\n",filename);
        printk(" 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
        printk(" -----------------------------------------------\n");

        ret = vfs_read(filp, buf, 1, &filp->f_pos);
        while(ret != 0){
            // (struct file *file, char __user *buf, size_t count, loff_t *offset)
            // Reads count bytes from the file offset position.
            // This action updates the file offset (*offset).
            printk(" %02X",buf[0]);
            ret = vfs_read(filp, buf, 1, &filp->f_pos);

            if(line_counter>=15)
            {
                line_counter=0;
                printk("\n");
            }
            else line_counter++;
        }
    }
    printk("\n");
    filp_close(filp, NULL);
    /* restore kernel memory setting */
    set_fs(old_fs);
}
