#include<limits.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#include"bit.h"
#include"compress.h"
#include"../algorithm/btree/btree.h"
#include"../algorithm/priority_queue/pqueue.h"

static int compare_freq(const void *tree1, const void *tree2) {
    HuffNode *root1,
             *root2;

    root1 = (HuffNode *)((((const BTree *)tree1)->root)->data);
    root2 = (HuffNode *)((((const BTree *)tree2)->root)->data);

    /* to create the min-heap */
    if (root1->freq < root2->freq)
        return 1;
    else if (root1->freq > root2->freq)
        return -1;
    else
        return 0;

}

static void destroy_tree(void *tree) {
    btree_destroy(tree);
    free(tree);
}

static int build_tree(int *freqs, BTree **tree) {
    BTree *init,
          *merge,
          *left,
          *right;

    PQueue pqueue;

    HuffNode *data;

    int c;                      /* process error, terminate the function */

    *tree = NULL;

    pqueue_init(&pqueue, compare_freq, destroy_tree);

    for( c = 0; c <= UCHAR_MAX; c++ ) {
        if(freqs[c] != 0) {
            /* set up a binary tree for the current symbol and its frequency */
            if((init = (BTree *)malloc(sizeof(BTree))) == NULL) {
                pqueue_destroy(&pqueue);
                return -1;
            }

            btree_init(init, free);
            if((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {
               pqueue_destroy(&pqueue);
               return -1;       /* process error, terminate the function */
            }

            data->symbol = c;
            data->freq = freqs[c];

            if(btree_ins_left(init, NULL, data) != 0) {
                free(data);
                btree_destroy(init);
                free(init);
                pqueue_destroy(&pqueue);
                return -1;      /* process error, terminate the function */
            }

            /* insert the binary tree into the priority_queue */
            if(pqueue_insert(&pqueue, init) != 0) {
                btree_destroy(init);
                free(init);
                pqueue_destroy(&pqueue);
                return -1;
            }
        }
    }

    /* build a huffman tree by merging trees in the priority_queue */
    for( c = 0; c < pqueue.size; c++) {
        /* allocate storage for the next merged tree */
        if((merge = (BTree *)malloc(sizeof(BTree))) == NULL) {
            pqueue_destroy(&pqueue);
            return -1;
        }

        /* extract the 2 trees whose root nodes have the smallest frequencies */
        if(pqueue_extract(&pqueue, (void **)&left) != 0) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }

        if(pqueue_extract(&pqueue, (void **)&right) != 0) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }

        /* allocate storage for the data in the root node of the merged tree */
        if((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }

        memset(data, 0, sizeof(HuffNode));

        /* sum the frequencies in the root nodes of the trees being merged */
        data->freq = ((HuffNode *)((left->root)->data))->freq
            + ((HuffNode *)((right->root)->data))->freq;

        /* merge the two trees */
        if(btree_merge(merge, left, right, data) != 0) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }

        /* insert the  merged tree into the priority_queue and free the others */
        if(pqueue_insert(&pqueue, merge) != 0) {
            pqueue_destroy(&pqueue);
            btree_destroy(merge);
            free(merge);
            return -1;
        }

        free(left);
        free(right);
    }

    /* the last tree priority_queueu is the huffman_tree */
    if(pqueue_extract(&pqueue, (void **)tree) != 0) {
        pqueue_destroy(&pqueue);
        return -1;
    } else
        pqueue_destroy(&pqueue);


    return 0;
}

static void build_table(BTreeNode *node,
        unsigned short code,
        unsigned char size,
        HuffCode *table) {
    if(!btree_is_eob(node)) {
        if(!btree_is_eob(node->left)) {
            /* move to the left and append 0 to the current code */
            build_table(node->left, code << 1, size + 1, table);
        }

        if(!btree_is_eob(node->right)) {
            /* move to the right and append 1 to the current code */
            build_table(node->right, (code << 1) | 0x0001, size + 1, table);
        }

        if(btree_is_eob(node->left) && btree_is_eob(node->right)) {
            /* ensure that the current code is in big-endian format */
            code = htons(code);

            /* assign the current code to the symbol in the leaf node */
            table[((HuffNode *)(node->data))->symbol].used = 1;
            table[((HuffNode *)(node->data))->symbol].code = code;
            table[((HuffNode *)(node->data))->symbol].size = size;
        }
    }
}


int huffman_compress(const unsigned char *original,
        unsigned char **compressed,
        int size) {
    BTree *tree;
    HuffCode table[UCHAR_MAX + 1];
    int freqs[UCHAR_MAX + 1],
        max,    /* the maximum frequency */
        scale,
        hsize,  /* header informantion size */
        ipos,
        opos,
        cpos,
        c,      /* common loop counter */
        i;
    unsigned char *comp, /* temp pointer for 'compressed'_output-parameter */
                  *temp;

    /* Initially, there is no buffer of compressed data. */
    *compressed = NULL;

    /* Get the frequency of each symbol in the original data */
    memset(freqs, 0, sizeof(int) * (UCHAR_MAX + 1));

    ipos = 0;

    while(size > 0 && ipos < size) {
        freqs[original[ipos]]++;
        ipos++;
    }

    /* scale the frequency to fit into the one byte */
    max = UCHAR_MAX;

    for( c = 0; c < UCHAR_MAX + 1; c++ )
        if(freqs[c] > max)
            max = freqs[c];             /* get the maximum frequency */

    for ( c = 0; c < UCHAR_MAX + 1; c++ ) {
        scale = (int)(freqs[c] / ((double)max / (double)UCHAR_MAX));

        if(scale == 0 && freqs[c] != 0)
            freqs[c] = 1;
        else
            freqs[c] = scale;
    }

    /* build the huffman tree and table of codes for the data */
    if(build_tree(freqs, &tree) != 0)
        return -1; /* process error, terminate the function */

    memset(table, 0, sizeof(HuffCode) * (UCHAR_MAX + 1));

    build_table(tree->root, 0x0000, 0, table);

    btree_destroy(tree);
    free(tree);

    /* write the header information */
    hsize = sizeof(int) + (UCHAR_MAX + 1);

    if((comp = (unsigned char *)malloc(hsize)) == NULL)
        return -1;

    memcpy(comp, &size, sizeof(int));

    for(c = 0; c <= UCHAR_MAX; c++)
        comp[sizeof(int) + c] = (unsigned char)freqs[c];

    /* comprecss the data */
    ipos = 0;
    opos = hsize * 8;

    while(ipos < size) {
        /* get the next symbol in the original data */
        c = original[ipos];

        /* write the code for the symbol to the buffer of compressed data */
        for(i = 0; i < table[c].size; i++) {
            if(opos % 8 == 0) {
                /* allocate another byte for the buffer of compressed data */
                if((temp = (unsigned char *)realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }
                comp = temp;
            }
            cpos = (sizeof(short) * 8) - table[c].size + i;
            bit_set(comp, opos, bit_get((unsigned char *)&table[c].code, cpos));
            opos++;
        }
        ipos++;
    }

    /* point to the buffer of compressed data */
    *compressed = comp;

    /* return the number of bytes in the compressed data */
    return ((opos - 1) / 8) + 1;
}

int huffman_uncompress(const unsigned char *compressed,
        unsigned char **original) {
    BTree *tree;
    BTreeNode *node;
    int freqs[UCHAR_MAX + 1],
        hsize,  /* header size */
        size,   /* original-data size */
        ipos,
        opos,
        state,
        c;      /* common loop */

    unsigned char *orig,
                  *temp;

    /* Initially there is no buffer of original data */
    *original = NULL;
    orig = NULL;

    /* get the header information from the buffer of compressed data */
    hsize = sizeof(int) + (UCHAR_MAX + 1);
    memcpy(&size, compressed, sizeof(int));

    memcpy(freqs, compressed + sizeof(int), UCHAR_MAX + 1);

    /* rebuild the huffman tree used previously to compress the data */
    if(build_tree(freqs, &tree) != 0)
        return -1;

    /* uncompress the data */
    ipos = hsize * 8;
    opos = 0;
    node = tree->root;

    while(opos < size) {
        /* get the next bit in the compressed data */
        state = bit_get(compressed, ipos);
        ipos++;

        if(state = 0) {
            /* move to the left */
            if(btree_is_eob(node) || btree_is_eob(node->left)) {
                btree_destroy(tree); /* process error */
                free(tree);
                return -1;
            } else
                node = node->left;
        } else /* 1 */ {
            /* move to the right */
            if(btree_is_eob(node) || btree_is_eob(node->right)) {
                btree_destroy(tree); /* process error */
                free(tree);
                return -1;
            } else
                node = node->right;
        }

        if(btree_is_eob(node->left) && btree_is_eob(node->right)) {
            /* write the symbol in the leaf node to the buffer of original data */
            if(opos > 0) {
                if((temp = (unsigned char *)realloc(orig, opos + 1)) == NULL) {
                    btree_destroy(tree);
                    free(tree);
                    free(orig);
                    return -1;
                }
                orig = temp;
            } else {
                if((orig = (unsigned char *)malloc(1)) == NULL) {
                    btree_destroy(tree);
                    free(tree);
                    return -1;
                }
            }

            orig[opos] = ((HuffNode *)(node->data))->symbol;
            opos++;
            /* move back to the top of the tree */
            node = tree->root;
        }
    }

        btree_destroy(tree);
        free(tree);

        /* point to the buffer of original data */
        *original = orig;

        /* return the number of bytes in the original data */
        return opos;
}
