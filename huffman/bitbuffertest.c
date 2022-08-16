#include <stdio.h>
#include "bit_buffer.h"

int main () {

    bit_buffer *b = bit_buffer_empty();
    bit_buffer_insert_byte(b, (char)68);
    bit_buffer_print(b);

    bit_buffer_insert_byte(b, (char)69);
    bit_buffer_print(b);

    bit_buffer_remove_byte(b);
    bit_buffer_print(b);

    bit_buffer_remove_byte(b);
    bit_buffer_print(b);

    bit_buffer_insert_byte(b, 'a');
    bit_buffer_print(b);

    bit_buffer_free(b);
    return 0;
}