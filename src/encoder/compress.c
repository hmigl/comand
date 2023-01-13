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

// TODO: chop down
static void compress(unsigned char *s) {
  int size = strlen((const char *)s);
  int i;

  if (size % 8 != 0) {
    int rem = 8 - (size % 8);
    while (rem--) {
      s[size++] = '0';
    }
    s[size] = '\0';
  }
  for (i = 0; i < size; i += 8) {
    unsigned char byte = 0;
    for (int j = 0; j < 8; j++) {
      byte = (byte << 1) | (s[i + j] - '0');
    }
    s[i / 8] = byte;
  }
  s[i / 8] = '\0';
}

void compress_data(aux_t *aux) {
  char *data_to_be_compressed = merge_input(aux->argc, aux->argv);
  list_t *freq_table = new_freq_table(data_to_be_compressed);
  // aux->encoded_data_length = strlen(data_to_be_compressed);

  aux->huff_tree = new_huff_tree(freq_table);
  int tree_height = huff_tree_height(aux->huff_tree);

  aux->dictionary = alloc_dictionary(FREQ_TABLE_SIZE, tree_height + 1);
  assemble_dictionary(aux->dictionary, aux->huff_tree, "", tree_height + 1);
  aux->compressed_data =
      (unsigned char *)encode(aux->dictionary, data_to_be_compressed);
  aux->encoded_data_length = strlen((char *)aux->compressed_data);
  compress(aux->compressed_data);
}
