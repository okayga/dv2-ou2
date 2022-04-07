#include <stdlib.h>
#include "bit_buffer.c"

freqtable *freqtable_create() {


    freqtable *ft = malloc(sizeof(freqtable));
    bit_buffer *b = bit_buffer_empty();

    for (int i = 0; i < 256; i++) {

        bit_buffer_insert_bit(b, i);
        ft.characters[i] = bit_buffer_to_byte_array(b);
        ft.frequency[i] = 0;
    }

    bit_buffer_free(b);
    return ft;
}

void freqtable_add_freq(freqtable *ft, int index) {

    ft.frequency[index]++;
}

void freqtable_destroy(freqtable *ft) {

    free(ft);
}
