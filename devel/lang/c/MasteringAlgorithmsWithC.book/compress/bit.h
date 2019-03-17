#ifndef BIT_H
#define BIT_H

/* the position describing the bit,
 * from 0 to 7, from first to eighth,
 * from left to right */

/* consider the problem about endian */

int bit_get(const unsigned char *bits,
        int pos); /* position */

void bit_set(unsigned char *bits,
        int pos, /* position */
        int state);

void bit_xor(const unsigned char *bits1,/* inputA */
        const unsigned char *bits2,     /* inputB */
        unsigned char *bitsx,           /* output */
        int size);                      /* unit is 'bit'*/

/* rotation to left */
void bit_rot_left(unsigned char *bits,
        int size,       /* unit is 'bit' */
        int count);     /* unit is 'bit'  */

#endif
