#include <stdlib.h>

freqtable *freqtable_create() {

  freqtable *ft = malloc(sizeof(freqtable));
  for (int i = 0; i < 256; i++) {
    ft.characters[i] = (char)i;
    ft.frequency[i] = 0;

  }
  return ft;
}

void freqtable_destroy(freqtable *ft) {

  free(ft);
}
