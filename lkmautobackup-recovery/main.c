#include <stdio.h>

#include <sys/io.h>
#include <sys/stat.h>

// Directory check function
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int main()
{
    char *dirname = "/backup";

    if (isDirectory(dirname) == 1)
        printf("Directory already exists.\n");
    else
        printf("Directory does not exist.\n");

    // char buffer[20] = { 0, };
    // FILE *fp = fopen("hello.txt", "r");
    // fread(buffer, sizeof(buffer), 1, fp);   // hello.txt에서 버퍼 크기(20바이트)만큼 1번 값을 읽음
    // printf("%s\n", buffer);    // Hello, world!: 파일의 내용 출력
    // fclose(fp);    // 파일 포인터 닫기

    return 0;
}