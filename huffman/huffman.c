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

bool validateInput (FILE *file) {

    FILE *filePtr = file;
    char ch;

    while ((ch = fgetc(filePtr)) != EOF) {
        if (ch > 0xff || ch < 0x00) {
            fclose(filePtr);
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {

    if ((strcmp(argv[1], "-encode") != 0 && strcmp(argv[1], "-decode") != 0) ||
    argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || (argc != 5)) {
        printf("USAGE:\n");
        printf("%s [OPTION] [FILE0] [FILE1] [FILE2]\n", argv[1]);
        printf("Options:\n");
        printf("-encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
        printf("-decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
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
    fseek(output_file, 0, SEEK_END);
    int size = ftell(output_file);
    if (size != 0) {
        printf("FILE2 is not empty. Please empty before rerunning this program\n");
        return 1;
    }

    freqtable *ft = frequencyCount(freq_file);
    pqueue *pq = freqtableToPq(ft);
    node *trie = pqToTrie(pq);
    table *t = initiateTable();
    bit_buffer *codes = bit_buffer_empty();
    trieToTable(trie, t, codes);

    if (strcmp(argv[1], "-encode") == 0) {
        /* This has to be done before entering the encode function to be able to
        access argv[3] */
        fseek(text_file, 0, SEEK_END);
        printf("%ld bytes read from %s.", ftell(text_file), argv[3]);
        fseek(text_file, 0, SEEK_SET);

        encode(t, text_file, output_file);
    } else {
        decode(trie, text_file, output_file);
    }

    freqtableKill(ft);
    pqueue_kill(pq);
    killTrie(trie);
    killTable(t);
    bit_buffer_free(codes);

    fclose(freq_file);
    fclose(text_file);
    fclose(output_file);
    return 0;
}
