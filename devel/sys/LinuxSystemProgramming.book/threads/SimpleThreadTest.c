#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *start_thread(void *message) {
    int i;
    for(i = 0; i < 4; i++)
        printf("%s\n", (const char *)message);
    return message;
}

int main(int argc, char **argv){
    pthread_t first_thread,
              second_thread;
    const char *first_message = "#######This is the first thread";
    const char *second_message = ">>>>>>>This is the second thread";

    /* create two threads,
     * each send a unique message. */

    pthread_create(&first_thread, NULL, start_thread, (void *)first_message);
    pthread_create(&second_thread, NULL, start_thread, (void *)second_message);

#if 1 /* 1, blocking, 0 no-blocking
         change it to witness the diff */
    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);
#endif
    int i;
    for ( i = 0; i < 4; i++ ) {
        printf("%s\n", "====== This the main thread");
    }


    return 0;
}
