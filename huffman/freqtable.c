#include <stdlib.h>

#include "freqtable.h"
#include "htrie.h"

/* Internal function for making the priority queue. If the return value is > 0
elem1 is larger, and if return value < 0 then elem2 is larger. */
int lessThan(void *elem1, void *elem2) {

    return ((node *)elem1)->prio - ((node *)elem2)->prio;
}

freqtable *frequencyCount(FILE *freq_file) {

    freqtable *ft = calloc(256, sizeof(freqtable));

    // Initiate the symbol array with every UTF-8 char
    for (int i = 0; i < 256; i++) {
        ft[i].symbol = (char)i;
    }

    char ch;
    while ((ch = fgetc(freq_file)) != EOF) {
        ft[(int)ch].freq++;
    }

    return ft;
}

pqueue *freqtableToPq (freqtable *ft) {

    pqueue *pq = pqueue_empty(lessThan);

    for (int i = 0; i < 256; i++) {
        node *e = malloc(1*sizeof(node));
        e->left_child = NULL;
        e->right_child = NULL;
        e->prio = ft[i].freq;
        e->val = ft[i].symbol;
        printf("Value inserted into pq is %c and its freq is %i\n", e->val,
        e->prio);
        pqueue_insert(pq, e);
    }

    return pq;
}

void freqtableKill(freqtable *ft) {

    free(ft);
}

void printFTable(freqtable *ft) {

    for (int i = 0; i < 256; i++) {
        printf("Row %d contains symbol %c and has frequency %d\n", i,
        ft[i].symbol, ft[i].freq);
    }
}
