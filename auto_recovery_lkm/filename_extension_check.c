#include "filename_extension_check.h"

char *check_fe(char *file_path, char *original_path)
{
    char *target_ext[] = {
        // document
        "txt",
        "ppt",
        "pptx",
        "xls",
        "doc",
        "docx",
        "pdf",

        // image
        "jpg",
        "png",

        // music
        "mp3",
        "flac",

        //media
        "mp4",
        "mkv"};

    char *str_tok=strsep(&file_path,".");
    char *final_tok=NULL;
    int iter = 0, flag=0;

    printk(KERN_ALERT "[*] checking... original path : %s\n", original_path);

    while(str_tok!=NULL)
    {
        final_tok=str_tok;
        //printk(KERN_ALERT "[*] check tok : %s", final_tok);
        str_tok=strsep(&file_path,".");
    }
    //printk(KERN_ALERT "[*] final tok : %s", final_tok);


    for(iter=0;iter<(int)ARRAY_SIZE(target_ext);iter++)
    {
        //printk(KERN_ALERT "[*] compare %s , %s",final_tok,target_ext[iter]);
        if(strcmp(target_ext[iter],final_tok)==0)
            flag=1;
            break;
    }

    if(flag==1)
    {
        return final_tok;
    }
    return NULL;
}