#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<sys/time.h>

#define NTHR (8)    /* number of threads */
#define NUMNUM (8000000L)       /* number of numbers to sort */
#define TNUM (NUMNUM / NTHR)    /* number of sort per thread */

long nums[NUMNUM];      /* src numbers */
long snums[NUMNUM];     /* sorted numbers */

pthread_barrier_t b;
#ifdef SOLARIS /* as solaris implements `heapsort()' */
#define heapsort qsort
#else
extern int heapsort(void *,
        size_t,
        size_t,
        int (*)(const void *, const void *));
#endif

/* compare two long integers */
int complong(const void *arg1, const void *arg2) {
    long long_int_left = *(const long *)arg1;
    long long_int_right = *(const long *)arg2;
    return (int)(long_int_left - long_int_right);
}

/* worker thread to sort a portion of the set of numbers */
void *thr_fn(void *arg) {
    long idx = (long)arg; /* this is not a elegant implement-way */
    heapsort(&nums[idx], TNUM, sizeof(long), complong);
    pthread_barrier_wait(&b);
    /* go off and perform more work ... */
    return ((void *)0);
}

/* merge the results of the individual sorted ranges */
void merge(void) {
    long idx[NTHR];
    long i, /* common counter */
         minidx, /* min - index */
         sidx,   /* s - index */
         num;    /* number */
    for(i = 0; i < NTHR; i++)
        idx[i] = i * TNUM;
    for(sidx = 0; sidx < NUMNUM; sidx++) {
        num = LONG_MAX;
        for(i = 0; i < NTHR; i++) {
            if((idx[i] < (i + 1) * TNUM) && (nums[idx[i]] < num)) {
                num = nums[idx[i]];
                minidx = i;
            }
        }
        snums[sidx] = nums[idx[minidx]];
        idx[minidx]++;
    }
}

int main(void) {
    unsigned long i;
    struct timeval start,
                   end;
    long long startusec, endusec;
    double elapsed;
    int err;
    pthread_t tid;

    /* create the initial set of numbers to sort. */
    srandom(1);
    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR + 1);
    for(i = 0; i < NTHR; i++) {
        err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
        if(err != 0)
            fprintf(stderr, "can't create thread");
    }
    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);

    /* print the sorted list */
    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(endusec - startusec) / 1000000.0;

    printf("sort took %.4f seconds\n", elapsed);
    for(i = 0; i < NUMNUM; i++)
        printf("%ld\n", snums[i]);
    exit(0);
}
