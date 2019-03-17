#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

int a[10];

void display_ary_int(int *const ary,
        const int num) {
    int i = 0; /* counter */
    for ( i = 0; i < num; i++ ) {
        printf("%d\t", ary[i]);
        if( (i + 1) % 10 == 0 )
            putchar('\n');
    }
}

void init_ary_random_int(int *const ary,
        const int num){
    int i = 0; /* counter */
    srand((unsigned)time(NULL));
    for ( i = 0; i < num; i++ ) {
        ary[i] = rand()/999999;
    }
}

int cmp_little2big(const void *left, const void *right, const size_t type){
    switch(type){
        case 8 :
            return (*(long *)left - *(long *)right);
            break;

        case 4 :
            return (*(int *)left - *(int *)right);
            break;

        case 2 :

            return (*(short *)left - *(short *)right);
            break;

        case 1 :
            return (*(char *)left - *(char *)right);
            break;

        default:
            fprintf(stderr, "Wrong array element type. Check your input\n");
            exit(EXIT_FAILURE);
    }
}

void insert_sort(void *data,
        int num, /* amount of the element */
        size_t esize, /* element size */
        int (*cmpfunc)(const void *, const void *, const size_t type)){
    char *ary = data; /* pointer to the input array */
    int i, j;

    void *key = (char *)malloc(esize); /* to store key value */
    if(key == NULL){ /* memory allocat error handle */
        fprintf(stderr, "Can't allocate neseccary memory\n"
                "Program has to be terminated\n");
        exit(EXIT_FAILURE);
    }

#if 1 /* insert sort method, core algorithm */
    for(j = 1; j < num; j++) {
        memcpy(key, &ary[j * esize], esize);
        i = j - 1;

        while((i >= 0)  &&  (cmpfunc( &ary[i * esize], key, esize) > 0)) {
            memcpy(&ary[(i + 1) * esize], &ary[i * esize], esize);
            i--;
        }

        memcpy(&ary[(i + 1) * esize], key, esize);
    }
    free(key);
#endif
}

void bubble_sort(void *data,
        int num, /* amount of the element */
        size_t esize, /* element size */
        int (*cmpfunc)(const void *, const void *, const size_t type)){

    char *ary = data; /* pointer to the input array */
    int i, j;


    void *trans = (char *)malloc(esize); /* to store media-trans value */
    if(trans == NULL){ /* memory allocat error handle */
        fprintf(stderr, "Can't allocate neseccary memory\n"
                "Program has to be terminated\n");
        exit(EXIT_FAILURE);
    }

#if 1 /* bubble sort method, core algorithm */
    for(j = 0; j < num; j++) {
        for(i = j + 1; i < num; i++) {
            if(cmpfunc( &ary[j * esize], &ary[i * esize], esize) > 0){
                memcpy(trans, &ary[i * esize], esize);
                memcpy(&ary[i * esize], &ary[j * esize], esize);
                memcpy(&ary[j * esize], trans, esize);
            }
        }

    }
    free(trans); /* key is useless now */
#endif
}

void quick_sort(void *data,
        int num, /* amount of the element */
        size_t esize, /* element size */
        int (*cmpfunc)(const void *, const void *, const size_t type)){
    char *ary = data; /* pointer to the input array */

    void *key = (char *)malloc(esize); /* to store media-trans value */
    if(key == NULL){ /* memory allocat error handle */
        fprintf(stderr, "Can't allocate neseccary memory\n"
                "Program has to be terminated\n");
        exit(EXIT_FAILURE);
    }

#if 1 /* quick sort method, core algorithm */
    memcpy(key, &ary[0 * esize], esize);
    int i = 0; /* head cursor */
    int j = num - 1; /* tail cursor */
    while(i < j){
        while((cmpfunc(key, &ary[j * esize], esize) <= 0) && (i < j))
            j--;
        memcpy(&ary[i * esize], &ary[j * esize], esize);

        while((cmpfunc(key, &ary[i * esize], esize) >= 0) && (i < j))
            i++;
        memcpy(&ary[j * esize], &ary[i * esize], esize);

        memcpy(&ary[i * esize], key, esize);
    }
    free(key); /* key is useless now */

    if(i > 1)
        /* do not call the func when the previos piece of the array less than 2 */
        quick_sort((void *)ary, i, esize, cmpfunc);

    j++;
    if((num - j) > 0)
        quick_sort(&ary[j * esize], (num - j), esize, cmpfunc);
#endif
}

int main(int argc, char **argv){
    srand((unsigned)time(NULL));
    int i;

    init_ary_random_int(a, 10);

    display_ary_int(a, 10);

    quick_sort(a, 10, sizeof(int), cmp_little2big);

    for(i = 0; i < 10; i++)
        printf("%d\t", a[i]);
    printf("\n");
    return EXIT_SUCCESS;
}
