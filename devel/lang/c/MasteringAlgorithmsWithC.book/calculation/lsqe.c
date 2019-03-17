void lsqe(const double *x,
        const double *y,
        int n,
        double *b1,
        double *b0) {
    double  sumx,
            sumy,
            sumx2,
            sumxy;

    int i;

    /* compuer the required summations */
    sumx = 0.0;
    sumy = 0.0;
    sumx2 = 0.0;
    sumxy = 0.0;

    for(i = 0; i < n; i++) {
        sumx += x[i];
        sumy += y[i];
        sumx2 += pow(x[i], 2.0);
        sumxy += (x[i] * y[i]);
    }

    /* computer the least-squares estimators */
    *b1 = (sumxy - ((sumx * sumy)/(double) n)) / (sumx2 - (pow(sumx, 2.0)/ (double)n));
    *b0 = (sumy - ((*b1) * sumx))/ (double)n;

    return;
}
