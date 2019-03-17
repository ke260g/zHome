#include<math.h>
#include<stdlib.h>
#include"nummeths.h"

int root(double (*f)(double x),
        double (*g)(double x),
        double *x,
        int *n,
        double delta) {
    int satisfied, i;

    /* use Newton's method to find a root of f */
    i = 0;
    satisfied = 0;

    while(!satisfied && i + 1 < *n) {
        /* determine the next iteration of x */
        x[i + 1] = x[i] - (f(x[i]) / g(x[i]));

        /* determine whether the desired approximation has been obtained */
        if(fabs(x[i + 1] - x[i]) < delta)
            satisfied = 1;

        /* prepare for the next iteration */
        i++;
    }

    /* even without iterating, indicate that one value has been stored in x */
    if(i == 0)
        *n = 1;
    else
        *n = i + 1;

    if(satisfied)
        return 0;
    else
        return -1;
}
