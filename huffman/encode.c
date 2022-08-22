#include <stdio.h>
#include <stdlib.h>

#include "bit_buffer.h"
#include "htable.h"


void encode (table *t, FILE *text_file, FILE *output_file) {

    char ch;
    int index;
    bit_buffer *output_buffer = bit_buffer_empty();

    // Add corresponding codes for each character in the text file to output buffer
    while ((ch = fgetc(text_file)) != EOF) {
        index = (int)ch;
        printf("the size for the code for %c is %d\n", ch, bit_buffer_size(t[index].codes));
        for (int i = 0; i < bit_buffer_size(t[index].codes); i++) {
            bit_buffer_insert_bit(output_buffer, bit_buffer_inspect_bit(t[index].codes, i));
        }
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