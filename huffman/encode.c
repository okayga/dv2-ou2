#include <stdio.h>
#include <stdlib.h>

#include "bit_buffer.h"
#include "htable.h"


void encode (table *t, FILE *text_file, FILE *output_file) {

    char ch = fgetc(text_file);
    bit_buffer *output_buffer = bit_buffer_empty();

    while ((ch = fgetc(text_file)) != EOF) {
        for (int i = 0; i < bit_buffer_size(t[(int)ch].codes); i++) {
            bit_buffer_insert_bit(output_buffer, bit_buffer_inspect_bit(t[(int)ch].codes, i));
        }
    }

    // Add an EOT to the table for when the output file is to be decoded
    bit_buffer_insert_byte(output_buffer, 4);


    printf("%d bytes used in encoded form.", bit_buffer_size(output_buffer) / 8);
    char *text_output = bit_buffer_to_byte_array(output_buffer);
    fwrite(text_output, 1, bit_buffer_size(output_buffer), output_file);
    
    bit_buffer_free(output_buffer);
    free (text_output);
}