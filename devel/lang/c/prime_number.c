#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define MAX_NUM (366) // a year

int is_prime_number(unsigned int number) {
    int i; // counter
    int k; // sqrt of the test number
    k = (int)sqrt((double)number);
    for(i = 2; i <= k; i++)
        if(number % i == 0)
            break;
    if(i > k)
        return 1;
    else
        return 0;
    return 0;
}

int main( int argc, char **argv ) {
    int i;
    int in_num;
    if(argc == 1) {
        for(i = 1; i <= MAX_NUM; i++)
            if(is_prime_number(i))
                printf("%d is prime number\n", i);
    } else if (argc == 2) {
        in_num = atoi(argv[1]);
        if(is_prime_number(in_num))
            printf("%d is prime number\n", in_num);
    }
    return 0;
}
