#include <asm/uaccess.h>

#include <linux/fcntl.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>

void print_flags(int flags);
void print_open_status(char *file_path, int flags);