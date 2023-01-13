#include "decoder.h"
#include <string.h>
#include <unistd.h>

int main(void) {
  data_t *block = map_block(PATHNAME, 0);

  if (block == NULL) {
    fprintf(stderr, "Couldn't get block\n");
    return 1;
  }
  printf("%p\n", block->data);
  printf("%s\n", block->data);
  for (int i = 0; i < FREQ_TABLE_SIZE; i++) {
    if (strlen(block->dictionary[i]) > 0)
      printf("%s\n", block->dictionary[i]);
  }
  for (int i = 0; i < MAX_NODES; i++) {
    printf("%c\n", block->serialized_tree[i]);
  }
  detach_block(block);
  return 0;
}
