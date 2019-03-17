/*
 * this is a single daemon program.
 * use mplayer to play a song.
 * from the given filename.
 */
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>

int ll_system(const char *cmd) {
    /*
     * fork of the system(),
     * but do not ignore any signle block
     */
    int ret;
    pid_t pid;
    pid = fork();
    if(pid == -1)
        return EXIT_FAILURE;
    else if (pid == 0) {
        const char *argvs[4] = { "sh", "-c", cmd, NULL};
        execv("/bin/sh", (char **)argvs);
        exit(-1);
    }
}

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage : %s <audio_file_name>\n\n", argv[0]);
        abort();
    }

    int ret;
    char *song = argv[1];
    char *play_argvs[5] = {
        "mplayer", "-loop", "0", song, NULL};

    int status = daemon(0, 0);
    ret = execv("/usr/bin/mplayer", play_argvs);
    if(ret == -1)
        abort();

    return status;
}
