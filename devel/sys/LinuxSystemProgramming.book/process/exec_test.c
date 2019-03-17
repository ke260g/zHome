#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc, char **argv){
    int ret = execlp("pinfo", "bison", NULL);
    if(ret == -1)
        perror("execl()");
    return EXIT_SUCCESS;
}
