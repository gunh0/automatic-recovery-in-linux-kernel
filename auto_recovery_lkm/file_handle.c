#include "file_handle.h"

void file_handle(char *filepath)
{
    struct file *filp;
    struct file *backup_fp;
    struct cred *old_cred;
    struct kstat orig_st;
    unsigned char buf[BUF_SIZE_500];
    int ret;
    // int line_counter = 0;

    struct timeval time;
    struct rtc_time tm;
    unsigned long local_time;
    char temp_str[BUF_SIZE_500];
    char backup_path_str[BUF_SIZE_500];
    unsigned int iter, iter2;

    char file_fingerprint[BUF_SIZE_500];

    /* kernel memory access setting */
    /* To use file function, unlock the kernel memory permission */
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);

    /* To use file function, get root permission */
    old_cred = (struct cred *)get_current_cred();
    commit_creds(prepare_kernel_cred(0));

    /* open a file */
    filp = filp_open(filepath, O_RDONLY, 0);

    /* To get file's system status data */
    memset(&orig_st, 0, sizeof(orig_st));
    vfs_stat(filepath, &orig_st);

    if (IS_ERR(filp))
    {
        printk("[-] filp_open error : %s\n\n", filepath);
        return;
    }
    else
    {
        printk("  [*] filp_open success : %s\n", filepath);
        printk("  [*] making backup file...\n");

        // time checking
        do_gettimeofday(&time);
        local_time = (u32)(time.tv_sec - (sys_tz.tz_minuteswest * 60));
        rtc_time_to_tm(local_time, &tm);
        printk("  [*] timestemp (GMT+9 KST | %04d%02d%02d-%02d%02d%02d)\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 9, tm.tm_min, tm.tm_sec);
        memset(&backup_path_str, 0, sizeof(backup_path_str));

        // backup dir checking
        strcat(backup_path_str, "/backup_dir/");
        backup_fp = filp_open(backup_path_str, O_DIRECTORY | O_RDONLY, 0);
        if (IS_ERR(backup_fp))
        {
            printk("[-] backup directory %s was not made.\n", backup_path_str);
            return;
        }
        else
        {
            printk("  [*] backup directory check... done.\n");
        }

        snprintf(temp_str, BUF_SIZE_500, "%04d", tm.tm_year + 1900);
        strcat(backup_path_str, temp_str);
        snprintf(temp_str, BUF_SIZE_500, "%02d", tm.tm_mon + 1);
        strcat(backup_path_str, temp_str);
        snprintf(temp_str, BUF_SIZE_500, "%02d", tm.tm_mday);
        strcat(backup_path_str, temp_str);
        strcat(backup_path_str, "-");
        snprintf(temp_str, BUF_SIZE_500, "%02d", tm.tm_hour + 9);
        strcat(backup_path_str, temp_str);
        snprintf(temp_str, BUF_SIZE_500, "%02d", tm.tm_min);
        strcat(backup_path_str, temp_str);
        snprintf(temp_str, BUF_SIZE_500, "%02d_", tm.tm_sec);
        strcat(backup_path_str, temp_str);
        for (iter = strlen(filepath) - 1; filepath[iter] != '/'; iter--)
            ;
        strcpy(temp_str, filepath + iter + 1);
        strcat(backup_path_str, temp_str);
        memset(&temp_str, 0, sizeof(temp_str));
        strcpy(temp_str, backup_path_str);

        // hide file extension in backupfile (.lkmautobackup)
        for (iter2 = strlen(temp_str) - 1; temp_str[iter2] != '.'; iter2--)
            ;
        memset(&backup_path_str, 0, sizeof(backup_path_str));
        strncpy(backup_path_str, temp_str, iter2);
        strcat(backup_path_str, ".lkmautobackup");
        printk("  [*] file name state : [%s]\n", backup_path_str);
        printk("  [*] make backup file fingerprint\n");
        printk("  [*] 1st. file name : %s\n", filepath + iter + 1);
        printk("  [*] 2nd. file name string size : %lu\n", strlen(filepath + iter + 1));

        memset(&file_fingerprint, 0, sizeof(file_fingerprint));

        snprintf(file_fingerprint, BUF_SIZE_500, "%04X", (unsigned int)strlen(filepath + iter + 1)); // set 2byte for filename string size
        strcat(file_fingerprint, filepath + iter + 1);
        printk("  [*] 3th. final file fingerprint : %s\n", file_fingerprint);

        /* copy origin file */
        backup_fp = filp_open(backup_path_str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (IS_ERR(backup_fp))
        {
            printk("[-] backup file error\n");
        }
        else
        {
            printk("  [*] backup file open success\n");

            // printk("  [*] print offset(h) | [%s]\n", filepath);
            // printk(" 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            // printk(" -----------------------------------------------\n");

            vfs_write(backup_fp, file_fingerprint, strlen(file_fingerprint), &backup_fp->f_pos);

            ret = vfs_read(filp, buf, 1, &filp->f_pos);
            while (ret != 0)
            {
                /* (struct file *file, char __user *buf, size_t count, loff_t *offset) */
                /* Reads count bytes from the file offset position. */
                /* This action updates the file offset (*offset). */
                // printk(" %02X", buf[0]);

                vfs_write(backup_fp, buf, 1, &backup_fp->f_pos);
                ret = vfs_read(filp, buf, 1, &filp->f_pos);

                // if (line_counter >= 15)
                // {
                //     line_counter = 0;
                //     printk("\n");
                // }
                // else
                //     line_counter++;
            }
            vfs_write(backup_fp, buf, 1, &backup_fp->f_pos);
        }
    }
    printk("\n");
    filp_close(filp, NULL);
    filp_close(backup_fp, NULL);

    /* Restore kernel memory setting */
    /* Lock the kernel memory permission */
    set_fs(old_fs);
}