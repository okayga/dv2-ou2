
/* A structure that keeps track of each UTF-8 character's corresponding
huffman code, that gets its codes from the trie. Used in both encoding
and decoding. */
typedef struct HuffmanTable {
    bit_buffer *codes;
    char symbol;
} table;

void trieToTable (node *trie);

void killTable(table *t);