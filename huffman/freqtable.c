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

    FILE *filePtr = freq_file;
    char ch;
    int n;

    while ((ch = fgetc(filePtr)) != EOF) {
        n = (int)ch;
        ft[n].freq++;
    }

    return ft;
}

pqueue *freqtableToPq (freqtable *ft) {

    pqueue *pq = pqueue_empty(lessThan);
    node *e = malloc(sizeof(node));

    for (int i = 0; i < 256; i++) {
        e->val = ft[i].symbol;
        e->prio = ft[i].freq;
        pqueue_insert(pq, e);
    }

    return pq;
}

void freqtableKill(freqtable *ft) {

    free(ft);
}