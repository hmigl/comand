#include "encoder.h"

static void display_received_stats(void) {
  data_t *block = map_block(PATHNAME, 0);

  if (block == NULL) {
    fprintf(stderr, "Couldn't get block\n");
    exit(1);
  }
  printf("-------------------------------------------------\n");
  printf("Decompressed data:       \n\n%s\n\n", block->data);
  printf("Total bytes:             \n\t%ld\n\n", block->data_length);
  printf("Total compressed bytes:  \n\t%ld\n\n", block->compressed_data_length);
  printf("Time to decompress (ms)  \n\t%d\n", block->time_to_decompress);
  printf("-------------------------------------------------\n");
}

static void set_block_data(data_t *block, aux_t *aux) {
  int index = 0;

  serialize_tree(aux->huff_tree, block->serialized_tree, &index);
  strcpy(block->data, (char *)aux->compressed_data);
  block->can_display_statistics = false;
  block->encoded_data_length = aux->encoded_data_length;
  block->compressed_data_length = aux->compressed_data_length;
  block->data_length = aux->data_length;
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

static void display_usage(void) {
  fprintf(stderr, "Usage: ./encoder [TEXT]...\n");
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
  while (!block->can_display_statistics)
    ;
  display_received_stats();
  detach_block(block);
  erase_block(PATHNAME);
  return 0;
}
