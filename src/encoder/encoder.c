#include "encoder.h"

#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define COLOR_RESET "\e[0m"

static void display_received_stats(data_t *block) {
  while (!block->can_display_statistics)
    ;
  size_t comp_data_len = block->compressed_data_length;
  size_t data_len = block->data_length;
  float reduction = 1 - ((float)comp_data_len / (float)data_len) * 100;

  printf("\n%sDecompressed data:%s\n\n%s%s%s\n\n",
		  BBLU, COLOR_RESET, BYEL, block->data, COLOR_RESET);
  printf("%sTotal bytes:%s\n\t%s%ld%s\n\n",
		  BBLU, COLOR_RESET, BYEL, block->data_length, COLOR_RESET);
  printf("%sTotal compressed bytes:%s\n\t%s%ld (%.2f%%) %s\n\n",
		  BBLU, COLOR_RESET, BYEL, block->compressed_data_length, reduction, COLOR_RESET);
  printf("%sTime to decompress (ms)%s\n\t%s%.2f%s\n",
		  BBLU, COLOR_RESET, BYEL, block->time_to_decompress, COLOR_RESET);
}

static void set_block_data(data_t *block, aux_t *aux) {
  int index = 0;

  serialize_tree(aux->huff_tree, block->serialized_tree, &index);
  block->can_display_statistics = false;
  block->encoded_data_length = aux->encoded_data_length;
  block->compressed_data_length = aux->compressed_data_length;
  block->data_length = aux->data_length;
  for (unsigned int i = 0; i < aux->compressed_data_length; i++) {
    block->data[i] = aux->compressed_data[i];
  }
}

static data_t *estabilish_ipc(aux_t *aux) {
  size_t data_length = strlen((char *)aux->encoded_data);
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

  if (!has_valid_input(argc)) {
    display_usage();
    return 1;
  }
  compress_data(&aux);
  block = estabilish_ipc(&aux);
  display_received_stats(block);
  detach_block(block);
  erase_block(PATHNAME);
  return 0;
}
