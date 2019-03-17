#include<stdio.h>
#include<stdlib.h>

long factorial(const long n, const long a){
    printf("n is %ld,  in %p\t", n, &n);
    printf("a is %ld,  in %p\n\n", a, &a);
    if(n <= 0)
        return 0;
    else if(n == 1)
        return a;
    else /* n > 1 */
        return factorial(n - 1, n * a);
}

int main(int argc, char **argv){
    long num = 9;
    printf("Factorial of %ld is %ld\n", num, factorial(num, 1));
    return EXIT_SUCCESS;
}
