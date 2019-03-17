#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char Dec2Hex_Char(const int dec) {
    /* return the hexadecimal character */
    /* when the dec is not a valid input(0< dec < 16),
     * return '\0' */
    if(0 <= dec && dec < 10)
        return '0' + dec;
    else if(dec < 16)
        return 'A' + (dec - 10);
    else
        return '\0'; /* error input */
}

int main(int argc, char **argv){
    int dec,
        src_dec; /* user define */

    printf("This program can convert a decimal to hexadecimal.\n");

    do{
        printf("Enter a positive decimal: ");
        scanf("%d", &src_dec); /* obtain the input */
    } while(src_dec < 0);

    dec = src_dec;

    int remainder;

    /* result of string */
    char *res = (char *)malloc(sizeof(char) * (1));
    res[0] = '\0';

    while(dec != 0) {
        remainder = dec % 16;

        char *tmp = (char *)malloc(sizeof(char) * (strlen(res) + 2));
        tmp[0] = Dec2Hex_Char(remainder);
        strncpy(tmp + 1, res, strlen(res));
        tmp[sizeof(tmp) + 1] = '\0';

        free(res);
        res = tmp;

        dec /= 16;
    }

    printf("The hexadecimal of decimal %d is 0x%s.\n", src_dec, res);
    return 0;
}
