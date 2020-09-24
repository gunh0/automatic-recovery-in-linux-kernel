/*
*  2020.09 DevGun
*
*  1. Verify that there is a backup directory created by LKM
*  2. Outputs a list of files to restore to the original file
*  3. Restore the corresponding file to its original state
*/

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include <sys/io.h>
#include <sys/stat.h>

// Directory check function
int isDirectory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

int main()
{
    char *dirname = "/backup";
    char recovery_path[256];
    char *filename = NULL;
    char fullpath[256];
    DIR *dp;
    struct dirent *dir;
    int file_cnt = 1;

    FILE *fp, *recovery_fp;

    if (isDirectory(dirname) != 1)
        printf("[-] Backup Directory does not exist.\n");

    else
    {
        printf("[+] Directory check... OK!\n");

        dp = opendir(dirname);
        if (dp)
        {
            while (dir = readdir(dp))
            {
                filename = dir->d_name;
                printf(" [*] (%3d) | %s\n", file_cnt++, filename);

                if (strstr(filename, ".lkmautobackup"))
                {
                    printf("  [*] This is backup file.\n");
                    strcpy(fullpath, dirname);
                    strcat(fullpath, "/");
                    strcat(fullpath, filename);
                    printf("  [*] %s\n", fullpath);

                    char buf[256] = {
                        0,
                    };
                    fp = fopen(fullpath, "r");
                    fread(buf, 4, 1, fp);

                    int origin_filename_size = (int)strtol(buf, NULL, 16);
                    printf("  [*] filename info. / length: %d\n", origin_filename_size);
                    memset(buf, 0, sizeof(char) * 256);
                    fread(buf, origin_filename_size, 1, fp);
                    printf("  [*] filename info. / string: %s\n", buf);
                    memset(recovery_path, 0, sizeof(char) * 256);
                    strcat(recovery_path, "/recovery_dir");
                    mkdir(recovery_path, 0777);
                    strcat(recovery_path, "/");
                    strcat(recovery_path, buf);
                    printf("  [*] recovery path: %s\n", recovery_path);

                    recovery_fp = fopen(recovery_path, "w+");
                }
            }
            printf("[+] List END.\n");
            closedir(dp);
            fclose(fp);
            fclose(recovery_fp);
        }
    }
}

// char buffer[20] = { 0, };
// FILE *fp = fopen("hello.txt", "r");
// fread(buffer, sizeof(buffer), 1, fp);   // hello.txt에서 버퍼 크기(20바이트)만큼 1번 값을 읽음
// printf("%s\n", buffer);    // Hello, world!: 파일의 내용 출력
// fclose(fp);    // 파일 포인터 닫기

// return 0;
// }