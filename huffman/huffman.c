#include <stdlib.h>
#include <stdio.h>

#include "freqtable.c"
#include "pqueue.c"
#include "bit_buffer.c"


bool validateInput (const char *filename) {

    FILE *filePtr;
    char current;

    filePtr = fopen(filename, "r");
    if (filePtr == NULL) {
        printf("Couldn't find file\n");
    } else {
        while ((ch = fgetc(filePtr)) != EOF) {
            if (ch > 0xff || ch < 0x00) {
                printf("File contains characters outside of UTF-8\n");
                fclose(filePtr);
                return false;
            }
        }
    }

    fclose(filePtr);
    return true;
}

void charFrequency(freqtable *ft, const char *filename) {

    FILE *filePtr;
    char current;

    filePtr = fopen(filename, "r");
    while ((ch = fgetc(filePtr)) != EOF) {
        ft.frequency[(int)ch]++;
    }

    ft.frequency[(int)EOF]++;
    fclose(filePtr);
}

pqueue *FreqTabletoPQueue(freqtable *ft) {

    for 
}

int main() {




    return 0;
}