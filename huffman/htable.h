#ifndef HTABLE_H
#define HTABLE_H

#include "bit_buffer.h"
#include "htrie.h"

/**
 * @defgroup h_table_h Huffman table header file
 *
 * @brief A module used to define the structure for a huffman table
 * and declares its functions.
 *
 * @author Maximilian Larsson - c20mln
 * @date 2022-08-21
 *
 * @{
 */

/**
 * @brief A structure that keeps track of each UTF-8 character's corresponding
 * huffman code, that gets its codes from the trie.
 */
typedef struct HuffTable {
    bit_buffer *codes;
    char symbol;
} table;

/**
 * @brief Creates a huffman table.
 *
 * @return table* - A pointer to the new huffman table.
 */
table *initiateTable ();

/**
 * @brief Converts a huffman trie to a huffman table.
 *
 * @param trie - A huffman trie.
 * @param t - The table to be filled.
 * @param bitBuffer - A bit buffer (for recursively adding codes from the
 * internal bit buffers)
 */
void trieToTable (node *trie, table *t, bit_buffer *bitBuffer);

/**
 * @brief Deallocates memory allocated by a huffman table.
 *
 * @param t - The huffman table to be deallocated.
 */
void killTable(table *t);

/**
 * @}
 */

#endif /* HTABLE_H */
