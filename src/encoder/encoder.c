#include "encoder.h"

static void display_usage(void) {
  fprintf(stderr, "Usage: ./encoder [TEXT]...\n");
}

static data_t *estabilish_ipc(int argc, char **argv) {
  data_t *block = map_block(PATHNAME, BLOCK_SIZE);

  if (block == NULL) {
    fprintf(stderr, "Couldn't get block\n");
    exit(1);
  }
  strcpy(block->data, merge_input(argc, argv));
  block->total_bytes = strlen(block->data);
  return block;
}

int main(int argc, char **argv) {
  data_t *block;

  if (!has_valid_input(argc, argv)) {
    display_usage();
    return 1;
  }
  block = estabilish_ipc(argc, argv);
  detach_block(block);
  return 0;
}
