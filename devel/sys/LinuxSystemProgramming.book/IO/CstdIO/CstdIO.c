/*
 * initialize a struct data
 * output it to the file, then close the file,
 * open the file and read the data write to a another struct data,
 * output such struct data to the stdout.
 */

#include<stdio.h>

int main(void) {
    FILE *in, *out;

    struct pirate {
        char name[100];
        unsigned long booty; /* pounds */
        unsigned int beard_len; /* inch */
    } p, blackbeard = { "Edward Teach", 950, 48};

    char *filename = "CstdIO_data";

    out = fopen(filename, "w");
    if(!out) {
        perror("fopen()");
        return 1;
    }

    if(!fwrite(&blackbeard, sizeof(struct pirate), 1, out)) {
        perror("fwrite()");
        return 1;
    }

    if(fclose(out)) {
        perror("fclose()");
        return 1;
    }

    in = fopen(filename, "r");
    if(!in) {
        perror("fopen()");
        return 1;
    }

    if(!fread(&p, sizeof(struct pirate), 1, in)) {
        perror("fread()");
        return 1;
    }

    if(fclose(in)) {
        perror("fclose()");
        return 1;
    }

    printf("name =\" %s \" booty = %lu beard_len=%u\n",
        (&p)->name, (&p)->booty, (&p)->beard_len);

    return 0;
}
