#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct mi {
    int nr;
    char *name;
} mi;

mi months[] = {
    { 1, "jan"}, { 2, "feb"}, { 3, "mar"}, { 4, "apr"},
    { 5, "may"}, { 6, "jun"}, { 7, "jul"}, { 8, "aug"},
    { 9, "sep"}, {10, "oct"}, {11, "nov"}, {12, "dec"}};

#define nr_of_months (sizeof(months)/sizeof(months[0])) /* the amount of months is 12 */
#define t_malloc(type) ((type *)malloc(sizeof(type)))

static int compmi(const void *m1, const void *m2) {
    return strcmp(((mi *)m1)->name, ((mi *)m2)->name);
}

int main(int argc, char **argv) {
    int i;
    qsort(months, nr_of_months, sizeof(mi), compmi);
    for(i = 1; i < argc; i++) {
        mi *key, *res;
        key = t_malloc(mi);
        key->name = argv[i];
        res = (mi *)bsearch(key, months, nr_of_months, sizeof(mi), compmi);
        if(res == NULL)
            printf("'%s' : unknown month\n", argv[i]);
        else
            printf("%s : month #%d\n", res->name, res->nr);
    }
    return EXIT_SUCCESS;
}
