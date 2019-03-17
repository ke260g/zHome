/* depth-first */
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<termio.h>
#include<unistd.h>

#include<dirent.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

#include<limits.h>

void rmfiles(const char *dir) {
    char * old_cwd = getcwd(NULL, 0);

    if(chdir(dir)) {
        printf("%s is not found\n", dir);
        return;
    }

    DIR * dp = opendir(".");
    struct dirent *direp = NULL;

    char * cwd = getcwd(NULL, 0);

    printf("%s\n", cwd);

    while(1) {
        direp = readdir(dp);
        if(!direp)
            break;
        char * dname = direp->d_name;
        int dtype = direp->d_type;
        if(!strcmp(dname, ".") || !strcmp(dname, ".."))
            continue;
        if(dtype == DT_DIR)
            rmfiles(dname);
        else {
            printf("%s/%s\n", cwd, dname);
            remove(dname);
        }
    }

    closedir(dp);
    chdir(old_cwd);
    remove(dir);

    free(cwd);
    free(old_cwd);
}

int main( int argc, char **argv ) {
    rmfiles("/tmp/ttyUSB");
    return 0;
}
