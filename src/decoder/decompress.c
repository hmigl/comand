#include "decoder.h"

void decompress(node_t *huff_tree, data_t *block) {
  int i, j, k = 0;
  node_t *current = huff_tree;
  char *decompressed = calloc(strlen(block->data) * 8 + 1, sizeof(char));

  for (i = 0; i < (int)strlen(block->data); i++) {
    for (j = 0; j < 8 && block->orig_data_length; j++) {
      if ((block->data[i] & (1 << (7 - j))) == 0) {
        if (current)
          current = current->left;
      } else {
        if (current)
          current = current->right;
      }
      if (current) {
        if (current->left == NULL && current->right == NULL) {
          decompressed[k++] = current->c;
          current = huff_tree;
        }
        block->orig_data_length--;
      }
    }
  }
  decompressed[k] = '\0';
  printf("Decompressed string: %s\n", decompressed);
  free(decompressed);
}
