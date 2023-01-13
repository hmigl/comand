#include "decoder.h"
#include <sys/time.h>

static unsigned int get_elapsed_time(struct timeval event) {
  struct timeval now;

  gettimeofday(&now, NULL);
  return (now.tv_sec * 1000 + now.tv_usec / 1000) -
         (event.tv_sec * 1000 + event.tv_usec / 1000);
}

static bool is_leaf(node_t *current) {
  return current && current->left == NULL && current->right == NULL;
}

static node_t *traverse_tree(node_t *current, char byte, int bit_index) {
  if ((byte & (1 << bit_index)) == 0) {
    current = current->left;
  } else {
    current = current->right;
  }
  return current;
}

static char *huffman_coding_decompress(node_t *huff_tree, data_t *block) {
  int i, j, k = 0;
  node_t *current = huff_tree;
  char *decompressed = calloc(strlen(block->data) * 8 + 1, sizeof(char));
  size_t compressed_data_length = block->compressed_data_length;
  block->compressed_data_length = strlen(block->data);

  for (i = 0; i < (int)strlen(block->data); i++) {
    for (j = 0; j < 8 && compressed_data_length; j++) {
      if (current) {
        current = traverse_tree(current, block->data[i], 7 - j);
      }
      if (current) {
        if (is_leaf(current)) {
          decompressed[k++] = current->c;
          current = huff_tree;
        }
        compressed_data_length--;
      }
    }
  }
  block->data_length = k;
  return decompressed;
}

void decompress(node_t *huff_tree, data_t *block) {
  struct timeval invocation_start;
  gettimeofday(&invocation_start, NULL);
  char *decompressed = huffman_coding_decompress(huff_tree, block);

  block->time_to_decompress = get_elapsed_time(invocation_start);
  strcpy(block->data, decompressed);
  free(decompressed);
}
