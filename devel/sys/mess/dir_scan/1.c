/* loop files in current diretory demo */
#include<errno.h>
#include<stdio.h>
#include<string.h>

#include<termio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

char bigbuf[BUFSIZ];

/* filter for scandir(), file *.jpg, *.png */
static int find_picture(const struct dirent *file)
{
    char *str_ret;
    struct stat stat_buf;
    stat(file->d_name, &stat_buf);

    /* whether a regular file */
    if ((stat_buf.st_mode & S_IFMT) != S_IFREG)
        return 0;

    /* find png suffix */
    str_ret = strstr(file->d_name, ".jpg");
    if(str_ret)
        if(strlen(str_ret) == 4)
            return 1; /* fonund */

    /* find jpg suffix */
    str_ret = strstr(file->d_name, ".png");
    if(str_ret)
        if(strlen(str_ret) == 4)
            return 1; /* found */

    return 0; /* not found */
}

int main(int argc, char **argv)
{

    int i,
        //j,
        ret,
        *retpt;

    struct dirent **result_list;

    printf("to find the *.png, *.jpg file in current diretory.\n");
    ret = scandir(getcwd(NULL, 0), &result_list, find_picture, alphasort);
    if(ret > 0) {
        for(i = 0; i < ret; i++) {
            printf(" %s \n", result_list[i]->d_name);
        }
    }
    return 0;

}
