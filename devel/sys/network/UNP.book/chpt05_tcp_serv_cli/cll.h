#ifndef __CLL_H
#define __CLL_H

#include<stdio.h>
#include<unistd.h>

#define __ll_debug()\
    do {fprintf(stderr, "File : %s || Line : %d || Func : %s\n\n", \
            __FILE__,  __LINE__, __func__);}while(0)\

#define __ll_erorr(content) \
    do {      \
        char *__ll_c_error_str = content; \
    fprintf(stderr, "Error : %s > File : %s > Line : %d > Func : %s\n\n", \
            __ll_c_error_str, __FILE__,  __LINE__, __func__);   \
    } while(0)\

#define __ll_swap(a, b, size)\
    do {\
        size_t __size = (size); \
        char *__a = (char *)(a); \
        char *__b = (char *)(b); \
        do { \
            char __tmp = *__a; \
            *__a++ = *__b; \
            *__b++ = tmp; \
        } while(--__size > 0); \
    } while(0)

#define __abs_usleep(us)            \
    do{ int volatile ret = 1;       \
        ret = usleep(us);           \
        while(ret)                  \
            ret = usleep(ret);      \
    } while(0)

#define __ll_execl(cmd_str_xxx_yyy) \
    (execl("/bin/sh", "-c", cmd_str_xxx_yyy, NULL))

#endif
