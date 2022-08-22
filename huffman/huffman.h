#ifndef HUFFMAN_H
#define HUFFMAN_H

/**
 * @defgroup huffman_h Huffman table header file
 * 
 * @brief A module used to define the functions used in the main driver
 * file.
 * 
 * @author Maximilian Larsson - c20mln
 * @date 2022-08-21
 * 
 * @{
 */

#include <stdlib.h>
#include <stdio.h>

#include "pqueue.h"
#include "bit_buffer.h"

/**
 * @brief Prints out instructions on how to use the huffman encoder/decoder
 * to the terminal.
 */
void usageHelp();

/**
 * @brief Validates the inputted file by checking if every character
 * is a UTF-8 character.
 * 
 * @param file - The file to be checked.
 * @return Returns true if the file is completely in UTF-8 characters. 
 * If not, returns false.
 */
bool validateInput (FILE *file);

/**
 * @}
 */

#endif /* HUFFMAN_H */