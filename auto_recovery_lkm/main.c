#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DevGun");
MODULE_DESCRIPTION("Auto Backup Linux Kernel Module");
MODULE_VERSION("-");

static int __init lkm_init(void)
{
    printk(KERN_INFO "[+] start LKM!!!\n");
    printk(KERN_ALERT "[+] MODULE INSERTED\n");
    return 0;
}

static void __exit lkm_exit(void)
{
    printk(KERN_INFO "[+] exit LKM...\n");
    printk(KERN_ALERT "[+] MODULE REMOVED\n");
}

module_init(lkm_init);
module_exit(lkm_exit);