#include "decoder.h"
#include <string.h>
#include <unistd.h>

int main(void) {
  data_t *block = map_block(PATHNAME, BLOCK_SIZE);

  if (block == NULL) {
    fprintf(stderr, "Couldn't get block\n");
    return 1;
  }
  printf("%p\n", block->data);
  printf("%s\n", block->data);
  detach_block(block);
  return 0;
}
