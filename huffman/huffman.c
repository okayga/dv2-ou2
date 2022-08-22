#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pqueue.h"
#include "bit_buffer.h"
#include "huffman.h"
#include "freqtable.h"
#include "htrie.h"
#include "htable.h"
#include "encode.h"
#include "decode.h"

void usageHelp() {
    printf("USAGE:\n");
    printf("./huffman [OPTION] [FILE0] [FILE1] [FILE2]\n");
    printf("Options:\n");
    printf("-encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
    printf("-decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
}

bool validateInput (FILE *file) {

    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch > 0xff || ch < 0x00) {
            fclose(file);
            return false;
        }
    }

    rewind(file);
    return true;
}

int main(int argc, char *argv[]) {

    // To avoid segmentation faults when only the run command is entered
    if (argc == 1) {
        usageHelp();
        return 1;
    }
    if ((strcmp(argv[1], "-encode") != 0 && strcmp(argv[1], "-decode") != 0) ||
    argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || (argc != 5)) {
        usageHelp();
        return 1;
    }

    FILE *freq_file, *text_file, *output_file;
    freq_file = fopen(argv[2], "r");
    text_file = fopen(argv[3], "r");
    output_file = fopen(argv[4], "w");

    if (!validateInput(freq_file)) {
        printf("FILE0 contains symbols outside of UTF-8");
        return 1;
    }
    if (!validateInput(text_file)) {
        printf("FILE1 contains symbols outside of UTF-8");
        return 1;
    }


    freqtable *ft = frequencyCount(freq_file);
    printFTable(ft);
    pqueue *pq = freqtableToPq(ft);
    node *trie = pqToTrie(pq);
    table *t = initiateTable();

    bit_buffer *empty_buffer = bit_buffer_empty();
    printTrie(trie, 0);
    trieToTable(trie, t, empty_buffer);
    bit_buffer_free(empty_buffer);

    if (strcmp(argv[1], "-encode") == 0) {
        /* This has to be done before entering the encode function to be able to
        access argv[3] */
        fseek(text_file, 0L, SEEK_END);
        printf("%ld bytes read from %s.\n", ftell(text_file), argv[3]);
        rewind(text_file);

        encode(t, text_file, output_file);
    } else {
        decode(trie, text_file, output_file);
    }

    freqtableKill(ft);
    pqueue_kill(pq);
    killTrie(trie);
    killTable(t);

    fclose(freq_file);
    fclose(text_file);
    fclose(output_file);
    return 0;
}
