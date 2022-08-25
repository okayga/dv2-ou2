#ifndef DECODE_H
#define DECODE_H

/**
 * @defgroup decode_h Huffman table header file
 * 
 * @brief A module used to define the function for decoding a huffman
 * coded file.
 * 
 * @author Maximilian Larsson - c20mln
 * @date 2022-08-21
 * 
 * @{
 */

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
 * @}
 */

#endif /* DECODE_H */