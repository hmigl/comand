#include "encoder.h"

static char **create_dictionary(int rows, int cols) {
  char **dictionary = malloc(rows * sizeof(char *));

  for (int i = 0; i < rows; i++) {
    dictionary[i] = calloc(cols, sizeof(char));
  }
  return dictionary;
}

void compress_data(int argc, char **argv) {
  char *data_to_be_compressed = merge_input(argc, argv);
  list_t *freq_table = new_freq_table(data_to_be_compressed);

  node_t *huff_tree = new_huff_tree(freq_table);
  int tree_height = huff_tree_height(huff_tree);

  char **dictionary = create_dictionary(FREQ_TABLE_SIZE, tree_height + 1);
  assemble_dictionary(dictionary, huff_tree, "", tree_height + 1);
}
