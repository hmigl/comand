#include "encoder.h"

static char **alloc_dictionary(int rows, int cols) {
  char **dictionary = malloc(rows * sizeof(char *));

  for (int i = 0; i < rows; i++) {
    dictionary[i] = calloc(cols, sizeof(char));
  }
  return dictionary;
}

static int data_length(char **dic, const char *data) {
  int i = -1, len = 0;

  while (data[++i]) {
    len += strlen(dic[(int)data[i]]);
  }
  len++;
  return len;
}

static char *encode(char **dic, const char *data) {
  char *encoded_data = calloc(data_length(dic, data), sizeof(char));

  for (int i = 0; data[i] != '\0'; i++) {
    strcat(encoded_data, dic[(int)data[i]]);
  }
  return encoded_data;
}

void compress_data(aux_t *aux) {
  char *data_to_be_compressed = merge_input(aux->argc, aux->argv);
  list_t *freq_table = new_freq_table(data_to_be_compressed);

  aux->huff_tree = new_huff_tree(freq_table);
  int tree_height = huff_tree_height(aux->huff_tree);

  aux->dictionary = alloc_dictionary(FREQ_TABLE_SIZE, tree_height + 1);
  assemble_dictionary(aux->dictionary, aux->huff_tree, "", tree_height + 1);
  aux->compressed_data = encode(aux->dictionary, data_to_be_compressed);
}
