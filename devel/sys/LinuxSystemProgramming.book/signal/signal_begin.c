#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

static void my_handler(int sig) {
    printf("This is my new signal handler.\n");
}

int main(int argc, char **argv){
    if(signal(SIGKILL, my_handler) == SIG_ERR) {
        fprintf(stderr, "Obviously, I can't reset the SIGKILL.\n");
        perror("failed to call signal() reset SIGKILL");
        putchar('\n');
    }

    if(signal(SIGSTOP, my_handler) == SIG_ERR) {
        fprintf(stderr, "Obviously, I can't reset the SIGSTOP.\n");
        perror("failed to call signal() reset SIGSTOP");
        putchar('\n');
    }

    if(signal(SIGTSTP, my_handler) == SIG_DFL) {
        printf("First time call signal(SIGTSTP, my_handler).\n");
        fprintf(stdout, "Successfully reset the signal handler.\n");
        putchar('\n');
    }

    if(signal(SIGTSTP, my_handler) == my_handler) {
        printf("Second time call signal(SIGTSTP, my_handler).\n");
        fprintf(stdout, "Successfully reset the signal handler.\n");
        putchar('\n');
    }


    printf("%p\n", &my_handler);
    printf("%p\n", my_handler);

    if(my_handler == &my_handler)
        printf("func == &func\n");
    while(1)
        ;

    return EXIT_SUCCESS;
}
