#include<stdio.h>
#include<unistd.h>

int main(int argc, char **argv){
    printf("argv[0] is %s\n", argv[0]);
    printf("%s\n", getcwd(NULL, 0));
    return 0;
}
