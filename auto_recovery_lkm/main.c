#include <asm/unistd.h>

#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rtc.h>
#include <linux/time.h>

#include "filename_extension_check.h"
#include "file_open.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DevGun");
MODULE_DESCRIPTION("Auto Backup Linux Kernel Module");
MODULE_VERSION("-");

char *target_dir = "/target_dir";
char *backup_dir = "/backup_dir";
char *file_ext=NULL;

void **sys_call_table;

asmlinkage int (*original_open)(const char *, int, mode_t);
asmlinkage int new_open(const char __user *pathname, int flags, mode_t mode)
{
    if (strstr(pathname, backup_dir))
    {
        printk(KERN_ALERT "[+] backup target : %s\n", pathname);
        return (*original_open)(NULL, flags, mode);
    }

    if (!strstr(pathname, target_dir))
        return (*original_open)(pathname, flags, mode);
    else
    {
        read_file((char *)pathname);

        file_ext=check_fe((char *)pathname);
        if(file_ext!=NULL){
        printk(KERN_ALERT "---------- path processing ----------\n");
        printk(KERN_ALERT "[+] target : %s\n", pathname);
        printk(KERN_ALERT "-[+] file ext : %s", file_ext);
        printk(KERN_ALERT "\n");
        }
    }
    return (*original_open)(pathname, flags, mode);
}

static void disable_page_protection(void)
{

    unsigned long value;
    asm volatile("mov %%cr0,%0"
                 : "=r"(value));
    if (value & 0x00010000)
    {
        value &= ~0x00010000;
        asm volatile("mov %0,%%cr0"
                     :
                     : "r"(value));
    }
}

static void enable_page_protection(void)
{

    unsigned long value;
    asm volatile("mov %%cr0,%0"
                 : "=r"(value));
    if (!(value & 0x00010000))
    {
        value |= 0x00010000;
        asm volatile("mov %0,%%cr0"
                     :
                     : "r"(value));
    }
}

static int __init lkm_init(void)
{
    struct timeval time;
    struct rtc_time tm;
    unsigned long local_time;

    do_gettimeofday(&time);
    local_time = (u32)(time.tv_sec - (sys_tz.tz_minuteswest * 60));
    rtc_time_to_tm(local_time, &tm);

    printk(KERN_INFO "[+] Start Auto Recovery LKM (DevGun)\n");

    disable_page_protection();

    // returned address of sys_call_table
    sys_call_table = (void *)kallsyms_lookup_name("sys_call_table");

    {
        original_open = sys_call_table[__NR_open];
        sys_call_table[__NR_open] = new_open;
    }

    enable_page_protection();
    printk(KERN_ALERT "[+] MODULE INSERTED (GMT+9 KST | %04d-%02d-%02d %02d:%02d:%02d)\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour+9, tm.tm_min, tm.tm_sec);
    return 0;
}

static void __exit lkm_exit(void)
{
    printk(KERN_INFO "[+] exit LKM...\n");
    disable_page_protection();

    {
        sys_call_table[__NR_open] = original_open;
    }

    enable_page_protection();
    printk(KERN_ALERT "[+] MODULE REMOVED\n");
}

module_init(lkm_init);
module_exit(lkm_exit);
