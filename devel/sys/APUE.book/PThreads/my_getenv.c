/*
 * implement a thread-safe getenv()
 *
 * using:
 *  pthread_key_create(), pthread_once(),
 *  pthread_getspecific(), pthread_setspecific()
 */
#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_STRING_LEN 4096

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thread_init(void) {
    pthread_key_create(&key, free);
}

char *getenv(const char *name) {
    int i, len;
    char * envbuf;

    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    envbuf = (char *)pthread_getspecific(key);
    if(envbuf == NULL) {
        envbuf = malloc(MAX_STRING_LEN);
        if(envbuf == NULL) {
            pthread_mutex_unlock(&env_mutex);
            return NULL;
        }
        pthread_setspecific(key, envbuf);
    }
    len = strlen(name);
    for(i = 0; environ[i] != NULL; i++) {
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
            strncpy(envbuf, &environ[i][len + 1], MAX_STRING_LEN - 1);
            pthread_mutex_unlock(&env_mutex);
            return envbuf;
        }

    }
    pthread_mutex_unlock(&env_mutex);
    return NULL;
}
