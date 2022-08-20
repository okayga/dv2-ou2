#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "pqueue.h"
#include "bit_buffer.h"
#include "huffman.h"
#include "freqtable.h"
#include "htrie.h"


bool validateInput (const char *filename) {

    FILE *filePtr;
    char ch;

    filePtr = fopen(filename, "r");
    if (filePtr == NULL) {
        printf("Couldn't find file\n");
    } else {
        while ((ch = fgetc(filePtr)) != EOF) {
            if (ch > 0xff || ch < 0x00) {
                fclose(filePtr);
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char *argv[]) {

    if ((strcmp(argv[1], "-encode") != 0 && strcmp(argv[1], "-decode") != 0) ||
    argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || (argc != 5)) {
        printf("USAGE:\n");
        printf("%s [OPTION] [FILE0] [FILE1] [FILE2]\n", argv[1])
        printf("Options:\n");
        printf("-encode encodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
        printf("-decode decodes FILE1 according to frequence analysis done on FILE0. Stores the result in FILE2\n");
        return 1;
    }

    FILE *freq_file, *text_file, *output_file;
    freq_file = fopen(argv[2], "r");
    text_file = fopen(argv[3], "r");
    output_file = fopen(argv[4], "w");

    if (!validateInput(file0)) {
        printf("FILE0 contains symbols outside of UTF-8");
    }
    if (!validateInput(file1)) {
        printf("FILE1 contains symbols outside of UTF-8");
    }
    fseek(output_file, 0, SEEK_END);
    int size = ftell(output_file);
    if (size != 0) {
        printf("FILE2 is not empty. Please empty before rerunning huffman.\n");
        return 1;
    }

    freqtable *ft = frequencyCount(file0);
    pqueue *pq = freqtableToPq(ft);
    node *trie = pqToTrie(pq);
    char option; 

    if (strcmp(argv[1], "-encode") == 0) {
        option = 'e';
    } else {
        option = 'd';
    }

     switch (option) {
        case ('e') {
            encode();
        }
        case ('d') {
            decode();
        }
    }

    freqtableKill(ft);
    pqueue_kill(pq);
    killTrie(trie);

    fclose(freq_file);
    fclose(text_file);
    fclose(output_file);
    return 0;
}
