#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "huffman.h"

void encode (table *t, FILE *text_file, FILE *output_file) {

    int ch = fgetc(text_file);
    int index;
    bit_buffer *output_buffer = bit_buffer_empty();

    // Add corresponding codes for each character in the text file to output buffer
    while (ch != EOF) {
        index = ch;
        for (int i = 0; i < bit_buffer_size(t[index].codes); i++) {
            bit_buffer_insert_bit(output_buffer, bit_buffer_inspect_bit(t[index].codes, i));
        }
        ch = fgetc(text_file);
    }

    // Add end of transmission (4) to the end of the output buffer
    bit_buffer *eot = bit_buffer_copy(t[4].codes);
    while (bit_buffer_size(eot) != 0) {
        bit_buffer_insert_bit(output_buffer, bit_buffer_remove_bit(eot));
    }
    bit_buffer_free(eot);

    printf("%d bytes used in encoded form.\n", bit_buffer_size(output_buffer) / 8);
    char *text_output = bit_buffer_to_byte_array(output_buffer);
    fwrite(text_output, 1, bit_buffer_size(output_buffer) / 8, output_file);
    
    bit_buffer_free(output_buffer);
    free (text_output);
}

void decode(node *trie, FILE *text_file, FILE *output_file) {

    int ch = fgetc(text_file);
    bit_buffer *output_buffer = bit_buffer_empty();

    while (ch != EOF) {
        bit_buffer_insert_byte(output_buffer, ch);
        ch = fgetc(text_file);
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
        } else {
            pointerToTrie = pointerToTrie->right_child;
        }
    }

    bit_buffer_free(output_buffer);
    printf("File decoded succesfully.\n");
}

void usageHelp() {
    printf("USAGE:\n");
    printf("./huffman [OPTION] [FILE0] [FILE1] [FILE2]\n");
    printf("Options:\n");
    printf("-encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
    printf("-decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
}

int main(int argc, char *argv[]) {

    // To avoid segmentation faults when only the run command is entered
    if (argc == 1) {
        usageHelp();
        return 1;
    }
    if (strcmp(argv[1], "-encode") != 0 && strcmp(argv[1], "-decode") != 0) {
        fprintf(stderr, "%s is not a valid option\n", argv[1]);
        usageHelp();
        return 1;
    }
    if (argv[2] == NULL) {
        fprintf(stderr, "Frequency file not provided\n");
        usageHelp();
        return 1;
    }
    if (argv[3] == NULL) {
        fprintf(stderr, "Text file not provided\n");
        usageHelp();
        return 1;
    }
    if (argv[4] == NULL) {
        fprintf(stderr, "Output file not provided\n");
        usageHelp();
        return 1;
    }
    if (argc > 5) {
        fprintf(stderr, "Too many arguments passed\n");
        usageHelp();
        return 1;
    }

    FILE *freq_file, *text_file, *output_file;
    if ((freq_file = fopen(argv[2], "rb")) == NULL) {
        fprintf(stderr, "%s does not exist or couldn't be opened \n", argv[2]);
        exit(EXIT_FAILURE);
    }

    if ((text_file = fopen(argv[3], "rb")) == NULL) {
        fprintf(stderr, "%s does not exist or couldn't be opened \n", argv[3]);
        fclose(freq_file);
        exit(EXIT_FAILURE);
    }
    
    // If the output file couldn't be created for some reason
    if ((output_file = fopen(argv[4], "wb")) == NULL) {
        fprintf(stderr, "The output file couldn't be created\n");
        fclose(freq_file);
        fclose(text_file);
        exit(EXIT_FAILURE);
    }
    
    freqtable *ft = calloc(256, sizeof(freqtable));

    frequencyCount(freq_file, ft);
    pqueue *pq = freqtableToPq(ft);
    node *trie = pqToTrie(pq);

    if (strcmp(argv[1], "-encode") == 0) {
        table *t = initiateTable();
        bit_buffer *empty_buffer = bit_buffer_empty();
        trieToTable(trie, t, empty_buffer);

        /* This has to be done before entering the encode function to be able to
        access argv[3] */
        fseek(text_file, 0L, SEEK_END);
        printf("%ld bytes read from %s.\n", ftell(text_file), argv[3]);
        rewind(text_file);
        encode(t, text_file, output_file);
        killTable(t);
    } else {
        decode(trie, text_file, output_file);
    }
    
    freqtableKill(ft);
    pqueue_kill(pq);
    killTrie(trie);
    
    fclose(freq_file);
    fclose(text_file);
    fclose(output_file);
    return 0;
}
