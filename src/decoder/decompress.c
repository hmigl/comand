#include "decoder.h"
#include <time.h>

static unsigned char *huffman_coding_decompress(node_t *huff_tree,
                                                data_t *block) {
  int i, j, k = 0;
  node_t *current = huff_tree;
  size_t data_length = block->data_length;
  unsigned char *decompressed =
      calloc(block->data_length + 1, sizeof(unsigned char));

  for (i = 0; i < (int)block->compressed_data_length; i++) {
    for (j = 7; j >= 0 && data_length; j--) {
      if (current) {
        current = (block->data[i] & (1 << j)) ? current->right : current->left;
      }
      if (current && current->left == NULL && current->right == NULL) {
        decompressed[k++] = current->c;
        current = huff_tree;
        data_length--;
      }
    }
  }
  decompressed[k] = '\0';
  return decompressed;
}

void decompress(node_t *huff_tree, data_t *block) {
  clock_t invocation_start = clock(), invocation_end;
  unsigned char *decompressed = huffman_coding_decompress(huff_tree, block);

  invocation_end = clock();
  block->time_to_decompress =
      (double)(invocation_end - invocation_start) / CLOCKS_PER_SEC * 1000;
  strcpy((char *)block->data, (char *)decompressed);
  free(decompressed);
}
