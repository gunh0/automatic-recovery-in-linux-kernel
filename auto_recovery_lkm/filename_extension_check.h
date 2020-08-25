#ifndef _SIGNATURE_H_
#define _SIGNATURE_H_

#include <linux/bug.h>
#include <linux/string.h>
#include <linux/kernel.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

char *check_fe(char *file_path);

#endif