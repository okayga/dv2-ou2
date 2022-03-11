/**
  * Compiles with:
  * gcc -Wall -std=c99 -o test_bit_buffer bit_buffer.c test_bit_buffer.c
  *
  * Just a short demonstration of usage of datatype pqueue.
  * The code lacks some comments.
  *
  * @author: Jonny Pettersson
  * @since:  2022-02-04
  */

#include <stdlib.h>
#include "bit_buffer.h"


int main()
{
	printf("\nAllocate the first bit buffer\n");
	bit_buffer *b1 = bit_buffer_empty();

	printf("\n-------- Hit return to continue... --------\n"); getchar();

	printf("Insert 35 alternating bit values, printed on the screen \n");
	printf("in chunks of 8 (for readability)\n\n");
	for (int i = 0 ; i < 35 ; i++) {
		if (i % 2) {
			bit_buffer_insert_bit(b1, true);
			printf("1");
		} else {
			bit_buffer_insert_bit(b1, false);
			printf("0");
		}
		if (i % 8 == 7) {
			printf(" ");
		}
	}
	printf("\n");

	printf("\n-------- Hit return to continue... --------\n"); getchar();

	printf("Create a byte array with the contents in the first \n");
	printf("bit buffer. Since we inserted 35 bits in to the first \n");
	printf("bit buffer, the bit buffer will be padded with five 0´s\n");
	char *byte_array = bit_buffer_to_byte_array(b1);

	printf("\n-------- Hit return to continue... --------\n"); getchar();

	printf("Free the first bit buffer\n");
	bit_buffer_free(b1);

	printf("\n-------- Hit return to continue... --------\n"); getchar();

	printf("Allocate a second bit buffer and insert the bytes \n");
	printf("from the byte array. In this case we know the number of \n");
	printf("bytes (35 inserted bits + five padded 0´s = 40 bits, \n");
	printf("then 40 bits diveded by 8). Then we free the byte array\n");

	bit_buffer *b2 = bit_buffer_create(byte_array, 40/8);
	free(byte_array);

	printf("\n-------- Hit return to continue... --------\n"); getchar();

	printf("Remove each bit, one by one, from the second bit \n");
	printf("buffer, and print them on the screen (the last five \n");
	printf("previously padded 0´s are now part of the information \n");
	printf("in the bit buffer)\n");
	int i = 0;
	while (bit_buffer_size(b2) > 0) {
		printf("%d", bit_buffer_remove_bit(b2));
		if (i % 8 == 7) {
			printf(" ");
		}
		i++;
	}
	printf("\n");

	printf("\n-------- Hit return to continue... --------\n"); getchar();

	printf("Free the second bit buffer\n\n");
	bit_buffer_free(b2);

	return 0;
}
