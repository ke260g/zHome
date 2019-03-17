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

void listfiles(const char *dir) {
    char * old_cwd = getcwd(NULL, 0);

    if(chdir(dir)) {
        printf("%s is not found\n", dir);
        return;
    }

    DIR * dp = opendir(".");
    if(!dp)
        return;

    char * cwd = getcwd(NULL, 0);
    struct dirent * dep = NULL;

    printf("%s\n", cwd);

    while(1) {
        dep = readdir(dp);

        if(!dep)
            break;

        char * dname = dep->d_name;
        int dtype = dep->d_type;
        if(!strcmp(dname, ".") || !strcmp(dname, ".."))
            continue;

        if(dtype == DT_DIR)
            listfiles(dname);
        else
            printf("%s/%s\n", cwd, dname);
    }

    closedir(dp);
    chdir(old_cwd);

    free(old_cwd);
    free(cwd);
}

int main( int argc, char **argv ) {
    listfiles("/etc/ppp");
    return 0;
}
