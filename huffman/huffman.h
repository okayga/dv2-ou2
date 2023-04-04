#ifndef HUFFMAN_H
#define HUFFMAN_H

/**
 * 
 * @mainpage Huffman encoder/decoder
 * 
 * @author Maximilian Larsson - c20mln
 * @since 2023-03-16
 * 
 * @section purpose What does this program do?
 * This program compresses a file by encoding it with Huffman coding. 
 * It takes a file for frequency analysis, a text file to be 
 * compressed, and an output file for where the coded text should be output.
 * The files need to be coded in UTF-8.
 * 
 * @section usage How to use the program
 * 
 * Run the program by typing ./huffman or .\huffman (depending on your operating system) in the console when in the huffman working directory. Then follow this synopsis:\n
 * huffman [OPTION] [FILE0] [FILE1] [FILE2]\n
 * [OPTION] is -encode or -decode, depending on what you want to do.\n 
 * [FILE0] is the file to run the frequency analysis on. The same frequency analysis file has to be used when encoding and decoding, otherwise the output will be incorrect\n
 * [FILE1] is the file to compress.\n
 * [FILE2] is the file to write the output to. The file doesn't need to exist before running this program, let [FILE2] denote the filename for the new file.
 * 
 * @section datastructures Data structures used
 * 
 * The huffman encoder/decoder uses several data structures:
 * - a frequency table, for the frequency analysis for every symbol
 * - a priority queue, that is used for constructing the huffman tree/trie. Constructed using a list
 * - a huffman trie, a node-based data structure that orders the letters by their frequency
 * and is used to construct the huffman code for each symbol
 * - a bit buffer, that inserts bits from one end and removes bits from another
 * - and a huffman table, that keeps track of the huffman codes
 * 
 * @section process Structure of the program
 * 
 * The basic structure of the program is as follows:
 * 
 * 1. Take FILE0 and count the frequency of every symbol
 * 2. Make a priority queue with all the symbols and prioritize them depending on how frequent they were
 * 3. Make a huffman tree/trie, where the symbols with the highest priority are closer to the root of the tree and vice versa
 * 4. Make a choice depending if the -encode or -decode flag was given
 *      - If -encode, make a huffman table containing each symbols code. 
 *      The code is calculated by following the huffman tree, adding a 0 to the code when following the 
 *      left child node, and 1 when following the right child node. 
 *      After getting the codes, read every character from FILE1 and convert them to a huffman coded symbol.
 *      - If -decode, convert each huffman coded symbol in the encoded file FILE1 to a character, by going left in the huffman trie when
 *      a 0 is read, and right when 1 is read. 
 * 5. Write the symbols to the output file FILE2
 * 
 */

/**
 * @defgroup huffman_h Huffman table header file
 *
 * @brief A module used to define the functions used in the main driver
 * file.
 *
 * @author Maximilian Larsson - c20mln
 * @date 2023-03-16
 *
 * @{
 */

#include <stdlib.h>
#include <stdio.h>

#include "pqueue.h"
#include "bit_buffer.h"
#include "freqtable.h"
#include "htrie.h"
#include "htable.h"

/**
 * @brief Encodes a given .txt file into huffman coding based on
 * earlier frequency analysis, and writes the text in coded form
 * in an output file.
 * 
 * @param ht - The huffman table.
 * @param text_file - A text file to be encoded.
 * @param output_file - The output file encoded in huffman code.
 */
void encode (table *ht, FILE *text_file, FILE *output_file);

/**
 * @brief Decodes a given huffman coded .txt file, based on 
 * frequency analysis of FILE0. The decoded text is given as a
 * .txt file as output.
 * 
 * @param trie - The huffman trie.
 * @param text_file - A text file to be decoded.
 * @param output_file - The decoded text file.
 */
void decode (node *trie, FILE *text_file, FILE *output_file);

/**
 * @brief Prints out instructions on how to use the huffman encoder/decoder
 * to the terminal when not enough arguments are given to the terminal.
 */
void usageHelp();

/**
 * @}
 */

#endif /* HUFFMAN_H */
