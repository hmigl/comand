#include "encoder.h"

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
// static unsigned int compress(unsigned char *s) {
//   int size = strlen((const char *)s);
//   int i;
//
//   if (size % 8 != 0) {
//     int rem = 8 - (size % 8);
//     while (rem--) {
//       s[size++] = '0';
//     }
//     s[size] = '\0';
//   }
//   for (i = 0; i < size; i += 8) {
//     unsigned char byte = 0;
//     for (int j = 0; j < 8; j++) {
//       byte = (byte << 1) | (s[i + j] - '0');
//     }
//     s[i / 8] = byte;
//   }
//   // s[i / 8] = '\0';
//   return size / 8;
// }

static unsigned int compress(unsigned char *s, char *compressed) {
  unsigned char mask, byte = 0;
  int i, j = 7, c_index = 0;
  // char *compressed = calloc(1000000, sizeof(char));

  for (i = 0; s[i]; i++) {
    mask = 1;
    if (s[i] == '1') {
      mask = mask << j;
      byte = byte | mask;
    }
    j--;
    if (j < 0) {
      compressed[c_index] = byte;
      c_index++;
      byte = 0;
      j = 7;
    }
  }
  if (j != 7) {
    compressed[c_index] = byte;
  }
  return c_index + 1;
}

void compress_data(aux_t *aux) {
  char *data_to_be_compressed = merge_input(aux->argc, aux->argv);
  list_t *freq_table = new_freq_table(data_to_be_compressed);
  aux->data_length = strlen(data_to_be_compressed);

  aux->huff_tree = new_huff_tree(freq_table);
  int tree_height = huff_tree_height(aux->huff_tree);

  aux->dictionary = alloc_dictionary(FREQ_TABLE_SIZE, tree_height + 1);
  assemble_dictionary(aux->dictionary, aux->huff_tree, "", tree_height + 1);
  aux->compressed_data =
      (unsigned char *)encode(aux->dictionary, data_to_be_compressed);
  aux->encoded_data_length = strlen((char *)aux->compressed_data);
  char *compressed = calloc(1000000, sizeof(char));
  aux->compressed_data_length = compress(aux->compressed_data, compressed);
  data_t block;
  unsigned int b = 0;
  b = aux->compressed_data_length;
  for (unsigned int i = 0; i < b; i++) {
    block.data[i] = compressed[i];
  }

  printf("after strcpy c.d.l: %u\n", aux->compressed_data_length);
  printf("%s\n", block.data);

  printf("-------------------------------------------------------------\n\n");
  block.compressed_data_length = b;
  // printf("fudeu? %u\n", b);
  char *a = huffman_coding_decompress(aux->huff_tree, &block);
  printf("%s\n", a);
  exit(42);
}
