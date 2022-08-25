#ifndef ENCODE_H
#define ENCODE_H

/**
 * @defgroup encode_h Encoding header file
 * 
 * @brief A module used to define the function for encoding a text 
 * to huffman coding.
 * 
 * @author Maximilian Larsson - c20mln
 * @date 2022-08-21
 * 
 * @{
 */

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
 * @}
 */

#endif /* ENCODE_H */