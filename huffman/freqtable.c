#include <stdlib.h>

#include "freqtable.h"
#include "htrie.h"

/* Internal function for making the priority queue. If the return value is > 0
elem1 is larger, and if return value < 0 then elem2 is larger. */
int lessThan(void *elem1, void *elem2) {

    return ((node *)elem1)->prio - ((node *)elem2)->prio;
}

void frequencyCount(FILE *freq_file, freqtable *ft) {

    // Initiate the symbol array with every UTF-8 char
    for (int i = 0; i < 256; i++) {
        ft[i].symbol = i;
    }

    char ch = fgetc(freq_file);
    while (ch != EOF) {
        ft[(int)ch].freq++;
        ch = fgetc(freq_file);
    }

    return;
}

pqueue *freqtableToPq (freqtable *ft) {

    pqueue *pq = pqueue_empty(lessThan);
  
    for (int i = 0; i < 256; i++) {
        node *e = calloc(1, sizeof(node));
        e->prio = ft[i].freq;
        e->val = ft[i].symbol;

        pqueue_insert(pq, e);
    }

    return pq;
}

void freqtableKill(freqtable *ft) {

    free(ft);
}
