#include <asm/uaccess.h>

#include <linux/cred.h>
#include <linux/fcntl.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rtc.h>
#include <linux/syscalls.h>
#include <linux/time.h>

#define BUF_SIZE_100 100
#define BUF_SIZE_50 50

void file_handle(char *filepath);
