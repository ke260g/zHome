#include<stdio.h>

int main(int argc, char **argv) {
    int target = 0x11223344;
    short *pt = (short *)&target;
    short val = *pt;

    if(val == 0x3344)
        printf("Little Endian\n");
    else if(val == 0x1122)
        printf("Big Endian\n");

    return 0;
}
