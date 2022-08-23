#include "htrie.h"

void decode(node *trie, FILE *text_file, FILE *output_file) {

    char ch = fgetc(text_file);
    bit_buffer *output_buffer = bit_buffer_empty();
    bit_buffer_insert_byte(output_buffer, ch);

    while ((ch = fgetc(text_file)) != EOF) {
        bit_buffer_insert_byte(output_buffer, ch);
    }
    
    // While output_buffer isn't empty, check if the current node is a leaf node
    node *pointerToTrie = trie;
    while (bit_buffer_size(output_buffer) > 0) {
        if (leafNode(pointerToTrie)) {
            fputc(pointerToTrie->val, output_file);
            pointerToTrie = trie;
        }
        if (bit_buffer_remove_bit(output_buffer) == 0) {
            pointerToTrie = pointerToTrie->left_child;
        }
        if (bit_buffer_remove_bit(output_buffer) == 1) {
            pointerToTrie = pointerToTrie->right_child;
        }
    }

    printf("File decoded succesfully.\n");
}