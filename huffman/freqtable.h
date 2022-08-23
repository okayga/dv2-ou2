#ifndef FREQTABLE_H
#define FREQTABLE_H

#include <stdio.h>

#include "pqueue.h"

/**
 * @defgroup freqtable_h Frequency table header file
 *
 * @brief A module used to define the structure for a frequency table
 * and declares its functions.
 *
 * @author Maximilian Larsson - c20mln
 * @date 2022-08-21
 *
 * @{
 */

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
 * @param freq_file - A pointer to the file to be analyzed.
 * @return freqtable* - A new frequency table.
 */
freqtable *frequencyCount(FILE *freq_file);

/**
 * @brief Converts a frequency table to a priority queue. The
 * priority queue has a "less than" comparing function.
 *
 * @param ft - The frequency table.
 * @return pqueue* - A new priority queue.
 */
pqueue *freqtableToPq (freqtable *ft);

/**
 * @brief Deallocates memory allocated by the frequency table.
 *
 * @param ft - The frequency table to be deallocated.
 */
void freqtableKill(freqtable *ft);

/**
 * @}
 */

#endif /* FREQTABLE_H */
