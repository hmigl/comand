#include "encoder.h"

static void display_usage(void) {
  fprintf(stderr, "Usage: ./encoder [TEXT]...\n");
}

static void set_block_data(data_t *block, aux_t *aux) {
  int index = 0;

  serialize_tree(aux->huff_tree, block->serialized_tree, &index);
  strcpy(block->data, (char *)aux->compressed_data);
  block->orig_data_length = aux->orig_data_length;
  block->data_length = strlen((char *)aux->compressed_data) + 1;
  for (int i = 0; i < FREQ_TABLE_SIZE; i++) {
    strcpy(block->dictionary[i], aux->dictionary[i]);
  }
}

static data_t *estabilish_ipc(aux_t *aux) {
  size_t data_length = strlen((char *)aux->compressed_data);
  data_t *block = map_block(PATHNAME, sizeof(data_t) + data_length + 1);

  if (block == NULL) {
    fprintf(stderr, "Couldn't get block\n");
    exit(1);
  }
  set_block_data(block, aux);
  return block;
}

int main(int argc, char **argv) {
  data_t *block;
  aux_t aux = {.argc = argc, .argv = argv};

  if (!has_valid_input(argc, argv)) {
    display_usage();
    return 1;
  }
  compress_data(&aux);
  block = estabilish_ipc(&aux);
  detach_block(block);
  return 0;
}
