/* ugly strtok(),
 * I implement a str_split()
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
 * str_split()
 * @param str input-param pointer to string
 * @param delim input-param pointer to delim
 * @param n output-param returns number of seperated string
 * @return an array of seperated string
 *
 * Note:
 *  caller has to free the returned array after using.
 *  it's not safe to modify the returned array
 *
 * str_splitFree()
 * @param strpv pointer to the returned array by str_split()
 */

char ** str_split(const char *str, const char *delim, int *n) {
    *n = 0;

    int len = strlen(str);
    char *s = (char *)malloc(len + 1);
    char **v = (char **)malloc((len) * sizeof(char *));
    memcpy(s, str, len);
    s[len] = '\0';

    int num = 0;
#if 0 /* strtok version */
    char *spt = strtok(s, delim);
    while(spt) {
        v[(*n)++] = spt;
        spt = strtok(NULL, delim);
    }
#else
    char *strp = s;
    char *spt = strsep(&strp, delim);
    while(spt) {
        v[(*n)++] = spt;
        spt = strsep(&strp, delim);
    }
#endif

    v = realloc(v, (*n) * sizeof(char *));

    return v;
}

void str_splitFree(char **strpv) {
    free(strpv[0]);
    free(strpv);
}

int main( int argc, char **argv ) {
    char str[] = "ab-bc-cd-ef";
    int len = strlen(str);

    int n = 0;
    char **v = str_split(str, "-", &n);
    int i;
    for(i = 0; i < n; i++) {
        printf("%s\n", v[i]);
    }
    str_splitFree(v);

    return 0;
}
