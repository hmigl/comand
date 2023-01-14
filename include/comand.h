#ifndef INCLUDE_COMAND_H_
#define INCLUDE_COMAND_H_

#include "../lib/comand_ipc/c_ipc.h"
#include "../lib/huffman/huffman_ds.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NODES 1000000

typedef struct data data_t;
struct data {
  unsigned int time_to_decompress;
  size_t data_length;
  size_t encoded_data_length;
  size_t compressed_data_length;

  bool can_display_statistics;
  char dictionary[256][256];
  int serialized_tree[MAX_NODES];
  char data[MAX_NODES];
};

#endif
