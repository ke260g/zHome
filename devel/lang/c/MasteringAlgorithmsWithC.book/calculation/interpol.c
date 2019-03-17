#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"nummeths.h"

int interpol(const double *x,
        const double *fx,
        int n,                  /* size of 'x' or 'fx' */
        const double *z,
        double *pz,
        int m) {                /* size of 'z' or 'pz' */

    double  term,
            *table,  /* table for difference_coefficients */
            *coeff;

    int i,
        j,
        k;

    /* allocate storage for the divided-difference table and coefficients */
    if((table = (double *)malloc(sizeof(double) * n)) == NULL)
        return -1; /* process error */

    if((coeff = (double *)malloc(sizeof(double) * n)) == NULL) {
        free(table);
        return -1;
    }

    /* initialize the coefficients */
    memcpy(table, fx, sizeof(double) * n);

    /* determine the coefficients of the interpolating polynomial */
    coeff[0] = table[0];
    for(k = 1; k < n; k++) {
        for(i = 0; i < n - k; i++) {
            j = i + k;
            table[i] = (table[i + 1] - table[i])/ (x[j] - x[i]);
        }

        coeff[k] = table[0];
    }

    free(table);

    /* evaluate the interpolating polynomial at the specified points */
    for(k = 0; k < m; k++) {
        pz[k] = coeff[0];

        for(j = 1; j < n; j++) {
            term = coeff[j];
            for(i = 0; i < j; i++)
                term *= (z[k] - x[i]);

            pz[k] += term;
        }
    }

    free(coeff);
    return 0;

