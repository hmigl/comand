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
    strcat((char *)encoded_data, dic[(int)data[i]]);
  }
  return encoded_data;
}

static unsigned int compress(char *encoded, char *compressed) {
  int i, j = 7, k = 0;
  unsigned char mask, byte = 0;

  for (i = 0; encoded[i]; i++) {
    mask = 1;
    if (encoded[i] == '1') {
      mask = mask << j;
      byte = byte | mask;
    }
    j--;
    if (j < 0) {
      compressed[k] = byte;
      k++;
      byte = 0;
      j = 7;
    }
  }
  if (j != 7) {
    compressed[k] = byte;
  }
  return k + 1;
}

void compress_data(aux_t *aux) {
  char *data_to_be_compressed = merge_input(aux->argc, aux->argv);
  list_t *freq_table = new_freq_table(data_to_be_compressed);
  aux->data_length = strlen(data_to_be_compressed);

  aux->huff_tree = new_huff_tree(freq_table);
  int tree_height = huff_tree_height(aux->huff_tree);

  aux->dictionary = alloc_dictionary(FREQ_TABLE_SIZE, tree_height + 1);
  assemble_dictionary(aux->dictionary, aux->huff_tree, "", tree_height + 1);
  aux->encoded_data = encode(aux->dictionary, data_to_be_compressed);

  aux->encoded_data_length = strlen((char *)aux->encoded_data);
  aux->compressed_data_length =
      compress(aux->encoded_data, (char *)aux->compressed_data);
}
