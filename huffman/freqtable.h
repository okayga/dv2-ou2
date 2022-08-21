#include <stdio.h>

#include "pqueue.h"

// A frequency table to construct the trie by calculating
// each UTF-8 characters frequency in a text.
typedef struct {
    int freq;
    char symbol;
} freqtable;

/**
 * @brief Creates a frequency table where the frequency
 * of every UTF-8 character in a text file is calculated,
 * and returns the frequency table. The frequency table
 * must later be deallocated.
 * 
 * @param filename The filename of the file to be analyzed.
 * @return freqtable* A frequency table.
 */
freqtable *frequencyCount(FILE *freq_file);

pqueue *freqtableToPq (freqtable *ft);

void freqtableKill(freqtable *ft);