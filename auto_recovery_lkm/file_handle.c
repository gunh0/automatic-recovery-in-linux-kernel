#include "file_handle.h"

void read_file(char *filename)
{
    struct file *filp;
    unsigned char buf[BUF_SIZE];
    int ret;
    int line_counter=0;

    struct timeval time;
    struct rtc_time tm;
    unsigned long local_time;
    char backup_path_str[BUF_SIZE];
    char temp_str[50];
 
    /* kernel memory access setting */
    /* To use file function, unlock the kernel memory permission */
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);
 
    /* open a file */
    filp = filp_open(filename, O_RDWR, S_IRUSR|S_IWUSR);
    if (IS_ERR(filp)) {
        printk("[-] filp_open error : %s\n\n",filename);
        return;
    }
    else
    {
        printk("[+] filp_open success : %s\n",filename);
        
        printk("-[*] making backup file...\n");

        // time checking
        do_gettimeofday(&time);
        local_time = (u32)(time.tv_sec - (sys_tz.tz_minuteswest * 60));
        rtc_time_to_tm(local_time, &tm);
        printk("-[*] timestemp (GMT+9 KST | %04d%02d%02d-%02d%02d%02d)\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour+9, tm.tm_min, tm.tm_sec);
        snprintf(temp_str,BUF_SIZE,"%d",tm.tm_year + 1900);
        strcat(backup_path_str, temp_str);
        snprintf(temp_str,BUF_SIZE,"%d",tm.tm_mon + 1);
        strcat(backup_path_str, temp_str);
        printk("-[*] state : [%s]\n",backup_path_str);

        printk("[*] print offset(h) | [%s]\n",filename);
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
    printk("\n\n");
    filp_close(filp, NULL);
    /* restore kernel memory setting */
    set_fs(old_fs);
}
