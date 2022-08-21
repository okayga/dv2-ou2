#include "bit_buffer.h"
#include "htrie.h"

/* A structure that keeps track of each UTF-8 character's corresponding
huffman code, that gets its codes from the trie. Used in both encoding
and decoding. */
typedef struct {
    bit_buffer *codes;
    char symbol;
} table;

table *initiateTable ();

void trieToTable (node *trie, table *t, bit_buffer *bitBuffer);

void killTable(table *t);