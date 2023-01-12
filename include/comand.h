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

typedef struct data data_t;
struct data {
  size_t data_length;
  char dictionary[256][256];
  char data[];
};

#endif
