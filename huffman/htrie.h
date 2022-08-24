#ifndef HTRIE_H
#define HTRIE_H

#include "list.h"
#include "pqueue.h"
#include "bit_buffer.h"

/**
 * @defgroup htrie_h Huffman table header file
 *
 * @brief A module used to define the structure for a huffman trie
 * and declares its functions.
 *
 * @author Maximilian Larsson - c20mln
 * @date 2022-08-21
 *
 * @{
 */

/**
 * @brief The structure for a node used in the huffman trie. It contains
 * an int val, which is the node's symbol, an int prio which is equivalent to its 
 * frequency, and two node pointers to the node's left and right child.
 */
typedef struct node {
    int val;
    int prio;
    struct node *left_child;
    struct node *right_child;
} node;

void printTrie(node *trie, int level);

/**
 * @brief Converts a priority queue to a huffman trie. The trie needs to 
 * be recursively deallocated later with the killTrie function.
 *
 * @param pq - The priority queue.
 * @return node* - A pointer to the root node in the trie.
 */
node *pqToTrie(pqueue *pq);

/**
 * @brief Checks whether a node in the trie is a leaf node or not.
 *
 * @param n - A node in the huffman trie.
 * @return If true, returns true. If false, returns false.
 */
bool leafNode(node *n);

/**
 * @brief Deallocates the allocated memory for a trie.
 *
 * @param trie - The trie to be deallocated.
 */
void killTrie(node *trie);

/**
 * @}
 */

#endif /* HTRIE_H */
