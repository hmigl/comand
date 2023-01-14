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
  return (byte & (1 << bit_index)) ? current->right : current->left;
}

static char *huffman_coding_decompress(node_t *huff_tree, data_t *block) {
  int i = 0, j, k = 0;
  node_t *current = huff_tree;
  char *decompressed = calloc(1, sizeof(char));

  // for (i = 0; i < block->compressed_data_length; i++) {
  while (i < (int)block->compressed_data_length) {
    // for (j = 0; j < 8 && k < block->data_length; j++) {
    for (j = 7; j >= 0; j--) {
      if (current) {
        current = traverse_tree(current, block->data[i], j);
      }
      if (is_leaf(current)) {
        printf("%c", current->c);
        decompressed[k++] = current->c;
        current = huff_tree;
        decompressed = realloc(decompressed, (k + 1) * sizeof(char));
      }
    }
    i++;
  }
  decompressed[k] = '\0';
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
