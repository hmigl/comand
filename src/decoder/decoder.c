#include "decoder.h"

int main(void) {
  data_t *block = map_block(PATHNAME, 0);
  node_t *huff_tree;
  int index = 0;

  if (block == NULL) {
    fprintf(stderr, "Couldn't get block\n");
    return 1;
  }
  huff_tree = deserialize_tree(block->serialized_tree, &index);
  decompress(huff_tree, block);
  block->can_display_statistics = true;
  detach_block(block);
  return 0;
}
