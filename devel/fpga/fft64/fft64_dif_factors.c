#include<stdio.h>
#include<math.h>
#define NUM (64)

#define PRECISION (8)
double factorRE[NUM];
double factorIM[NUM];
int re_pr[NUM];
int im_pr[NUM]; // round-result
#define REG_IM "factorIM"
#define REG_RE "factorRE"

int entry(void) {
    // calculate the factors, both real and imaginary parts
    int i;
    for(i = 0; i < NUM; i++) {
        factorRE[i] = cos(2 * M_PI * i/ (double)NUM);
        factorIM[i] = -sin(2 * M_PI * i/ (double)NUM);
        printf("%3d real-factor: %8.4lf imaginary-factor: %8.4lf\n", i, factorRE[i], factorIM[i]);
    }
    // quantize the factor, 8-bit precision
    for(i = 0; i < NUM; i++) {
        re_pr[i]  = factorRE[i] * ((1 << (PRECISION - 1))- 1);
        im_pr[i] = factorIM[i] * ((1 << (PRECISION - 1))- 1);
    }

    printf("==========================\n");
    for(i = 0; i < NUM; i++) {
        printf("%s[%d] <= ", REG_RE, i);
        if(re_pr[i] < 0)
            printf("-");
        printf("%d'd%d;  ", PRECISION, abs(re_pr[i]));

        printf("%s[%d] <= ", REG_IM, i);
        if(im_pr[i] < 0)
            printf("-");
        printf("%d'd%d;\n", PRECISION, abs(im_pr[i]));
    }
}

int main( int argc, char **argv ) {
    entry();
    return 0;
}
