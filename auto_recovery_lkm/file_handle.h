#include <asm/uaccess.h>

#include <linux/fcntl.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rtc.h>
#include <linux/syscalls.h>
#include <linux/time.h>

#define BUF_SIZE 100

void read_file(char *filename);
