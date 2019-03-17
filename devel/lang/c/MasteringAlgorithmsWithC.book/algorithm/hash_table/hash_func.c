#include"hash_func.h"

unsigned int hash_func_str(const void *key) {
    /*
     * This func is better to be used on strings.
     * Modified from the book,
     *      Compilers: Principles, Techniques, and Tools
     *          written by Alfred V.Aho, Ravi Sthi and Jeffrey D. Ullman
     */

    const char *ptr = key;
    unsigned int val = 0;

    while(*ptr != 0) {
        unsigned int tmp;
        val = (val << 4) + (*ptr);

        if(tmp = (val & 0xf0000000)) {
            /* once val's the 4 highest bit has at any one  '1' bit */
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }

        ptr++;
    }
    return val % HASH_TABLE_SIZE;
}
