/*
 * an implementation of 'ls' cmd,
 * with the 'quick_sort'
 */

#ifndef DIRECTLS_H
#define DIRECTLS_H

#include<dirent.h>

typedef struct Directory_ {
    char name[MAXNAMLEN + 1];
    /*  'MAXNAMLEN' is a macro defined in <dirent.h> */
} Directory;

/* public interface */
int directory(const char *path, Directory **dir);

#endif
