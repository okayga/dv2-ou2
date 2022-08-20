#include "freqtable.h"

/**
 * @brief Creates a frequency table where the frequency
 * of every UTF-8 character in a text file is calculated,
 * and returns the frequency table. The frequency table
 * must later be deallocated.
 * 
 * @param filename - The filename of the file to be analyzed.
 * @return freqtable* - A frequency table.
 */
freqtable *frequencyCount(const char *filename) {

    freqtable *ft = calloc(256, sizeof(freqtable));

    // Initiate the symbol array with every UTF-8 char
    for (int i = 0; i < 256; i++) {
        ft[i].symbol = (char)i;
    }

    FILE *filePtr;
    char ch;
    int n;

    filePtr = fopen(filename, "r");
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
    
    free(ft->freq);
    free(ft->symbol);
    free(ft);
}