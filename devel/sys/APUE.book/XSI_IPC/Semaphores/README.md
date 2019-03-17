# XSI semaphore diagram
### interface
+ `#include <sys/sem.h>`
+ `semid = semget(key, nsems, flag)` nsems is usually set to 1
+ `semctl(semid, sem_num, cmd, semun_arg)`
+ `semop(semid, semop_array [], nops)`
+ `union semun { } semun_arg`
+ `struct semop semop_array[#]`

---
## a normal diagram of semaphore
+ only one sem in the set
+ only one sync step, semval is 1 or 0
+ pA and pB is processes
### init:
+ file: semDia_init
```C
    key_t key = ftok
    semid = semget(key, 1, 0644 | IPC_CREAT);

    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } semun_arg;
    semun_arg.val = 1;
    semctl(semid, 0, SETVAL, semun_arg);
```

### sync-and-block: (pA and pB)
+ file: semDia_sync.c
```C
    key_t key = ftok
    semid = semget(key, 1, 0644 /* | IPC_CREAT */);
    struct sembuf semop_obj = { .sem_num = 0, .sem_op = -1, .sem_flg = SEM_UNDO, };
    semop(semid, &semop_obj, 1);
    /* ... donig ... */
```

### Note:
+ if a object can be access by n processes at a same time
+ then set semval to n
+ each processes `semop_array[#].semop = -1` before access
+ it must be done with `semop_array[#].sem_flg = SEM_UNDO`
+ without SEM\_UNDO, process-termination(without exit) will cause catastrophe
