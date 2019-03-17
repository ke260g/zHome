#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_t tid;
pthread_cond_t cond_lock = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

void *first_thread(void *arg) {
    printf("%s start to lock the mutex.\n", __func__);
    pthread_mutex_lock(&mutex_lock);

    printf("%s start to wait the cond.\n", __func__);
    pthread_cond_wait(&cond_lock, &mutex_lock);
    printf("%s cond_wait() return.\n", __func__);
}

void *second_thread(void *arg) {
    printf("%s start to lock the mutex.\n", __func__);
    pthread_mutex_lock(&mutex_lock);
    printf("%s mutex_lock return.\n", __func__);

    printf("%s cond_signal.\n", __func__);
    pthread_cond_signal(&cond_lock);
    printf("%s cond_signal return.\n", __func__);

    // if without below, first_thread will not release
    pthread_mutex_unlock(&mutex_lock);
}

int main(int argc, char **argv) {
    pthread_create(&tid, NULL, first_thread, NULL);
    sleep(2);
    pthread_create(&tid, NULL, second_thread, NULL);
    sleep(5);
    printf(" main() terminate.\n");
    return 0;
}
