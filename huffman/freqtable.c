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

    // Don't forget the EOF!
    ft[4].freq++;
    return ft;
}

pqueue *freqtableToPq (freqtable *ft) {

    pqueue *pq = pqueue_empty(lessThan);
    node *e = calloc(1, sizeof(node));
    e->left_child = NULL;
    e->right_child = NULL;

    for (int i = 0; i < 256; i++) {
        e->val = ft[i].symbol;
        e->prio = ft[i].freq;
        pqueue_insert(pq, e);
    }

    free(e);
    return pq;
}

void freqtableKill(freqtable *ft) {

    free(ft);
}