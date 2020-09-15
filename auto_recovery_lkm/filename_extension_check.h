#include <linux/bug.h>
#include <linux/string.h>
#include <linux/kernel.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define BUF_SIZE_100 100
#define BUF_SIZE_50 50

char *check_fe(char *file_path, char *copy_path);