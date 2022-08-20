table *initiateTable () {

    table *t = malloc(256*sizeof(table));
    for (int i = 0; i < 256; i++) {
        t->symbol[i] = (char)i;
    }
    
    return t;
}

void trieToTable (node *trie, table t, bit_buffer *bitBuffer) {
    if (isLeaf(trie) == 0) {
        t[(int)trie->val].symbol = trie->symbol;
        t[(int)trie->val].codes = bitBuffer;
    } else {
        
    /* The input buffer follows the left nodes recursively, and the
    second buffer follows the right nodes. */
    bit_buffer *secondBuffer = bit_buffer_copy(bitBuffer);
    bit_buffer_insert_bit(firstBuffer, 0):
    bit_buffer_insert_bit(secondBuffer, 1);

    trieToTable(node->left_child, t, bitBuffer);
    trieToTable(node->right_child, t, secondBuffer);
    }
}

void killTable(table *t) {
    for (int i = 0; i < 256; i++) {
        bit_buffer_free(t->codes[i]);
    }
    free(t);
}