#include <stdlib.h>

freqtable freqtable_create() {

  freqtable ft = malloc(sizeof(freqtable));
  for (int i = 0; i < 256; i++) {
    ft[i][1] =
  }
}

void freqtable_destroy(freqtable ft) {

  free(ft);
}
