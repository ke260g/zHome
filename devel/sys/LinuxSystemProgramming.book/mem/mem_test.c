#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv) {
    char *a = (char *)malloc(sizeof(char)+110);
    if(a == NULL) {
        fprintf(stderr, "malloc() failed");
        exit(EXIT_FAILURE);
    }

    if(!mallopt(M_CHECK_ACTION, 1)) {
        fprintf(stderr, "mallopt() failed");
        exit(EXIT_FAILURE);
    }

    printf("a available space is %ld\n",
            malloc_usable_size(a));

    *a = 10;
    printf("*a == %d\n", *a);
    free(a);
    free(a);

    malloc_stats();
    return EXIT_SUCCESS;
}
