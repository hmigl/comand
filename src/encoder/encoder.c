#include "encoder.h"

static void display_usage(void) {
  fprintf(stderr, "Usage: ./encoder [TEXT]...\n");
}

static void set_block_data(data_t *block, const char *encoded_data) {
  strcpy(block->data, encoded_data);
  block->data_length = strlen(encoded_data) + 1;
}

static data_t *estabilish_ipc(const char *encoded_data) {
  size_t data_length = strlen(encoded_data);
  data_t *block = map_block(PATHNAME, sizeof(data_t) + data_length + 1);

  if (block == NULL) {
    fprintf(stderr, "Couldn't get block\n");
    exit(1);
  }
  set_block_data(block, encoded_data);
  return block;
}

int main(int argc, char **argv) {
  data_t *block;

  if (!has_valid_input(argc, argv)) {
    display_usage();
    return 1;
  }
  block = estabilish_ipc(merge_input(argc, argv));
  detach_block(block);
  return 0;
}
