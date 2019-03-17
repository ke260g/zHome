#include<stdio.h>
#include<errno.h>
#include<limits.h>
int parse_args_port(const char  *port_str, int *num) {
    int base;
    char *endptr, *str;
    long val;

    // base = (argc > 2) ? atoi(argv[2]) : 10;
    base = 10;
    errno = 0;    /* To distinguish success/failure after call */
    val = strtol(port_str, &endptr, base);

    /* Check for various possible errors */
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        // perror("strtol");
        fprintf(stderr, "port specified is not a number: %s\n", port_str);
        return -1;
    }

    if (endptr == str) {
        fprintf(stderr, "No digits were found\n");
        return -1;
    }

    /* If we got here, strtol() successfully parsed a number */
    // printf("strtol() returned %ld\n", val);
    *num = val;

    if (*endptr != '\0') {       /* Not necessarily an error... */
        //printf("Further characters after number: %s\n", endptr);
        fprintf(stderr, "port specified is not a number: %s\n", port_str);
        return -1;
    }

    if(val < 1 || val > 65535) {
        fprintf(stderr, "port: %ld is out of range 1~65535\n", val);
        return -1;
    }

    return 0;
}
