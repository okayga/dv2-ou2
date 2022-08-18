#include <stdlib.h>
#include <stdio.h>

#include "pqueue.h"
#include "bit_buffer.h"


bool validateInput (const char *filename);

/**
 * @brief Creates a frequency table where the frequency
 * of every UTF-8 character in a text file is calculated,
 * and returns the frequency table. The frequency table
 * must later be deallocated.
 * 
 * @param filename The filename of the file to be analyzed.
 * @return freqtable* A frequency table.
 */
freqtable *frequencyCount (const char *filename);