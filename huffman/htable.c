#include <stdlib.h>

#include "htable.h"
#include "bit_buffer.h"
#include "htrie.h"

table *initiateTable () {

    table *t = calloc(256, sizeof(table));
    for (int i = 0; i < 256; i++) {
	    t[i].codes = bit_buffer_empty();
    }
    return t;
}

void trieToTable (node *trie, table *t, bit_buffer *bitBuffer) {

    if (leafNode(trie)) {
        int index = (char)trie->val;
        t[index].symbol = trie->val;
        t[index].codes = bitBuffer;
    }
    /* The input buffer follows the left nodes recursively, and the
    second buffer follows the right nodes. */
    bit_buffer *secondBuffer = bit_buffer_copy(bitBuffer);

    bit_buffer_insert_bit(bitBuffer, 0);
    bit_buffer_insert_bit(secondBuffer, 1);


    if (trie->left_child != NULL) {
        trieToTable(trie->left_child, t, bitBuffer);
    }
    if (trie->right_child != NULL) {
        trieToTable(trie->right_child, t, secondBuffer);
    }
}

void killTable(table *t) {

    for (int i = 0; i < 256; i++) {
        bit_buffer_free(t[i].codes);
    }
    free(t);
}
