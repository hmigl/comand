#ifndef SRC_ENCODER_ENCODER_H_
#define SRC_ENCODER_ENCODER_H_

#include "../../include/comand.h"

typedef struct aux aux_t;
struct aux {
  char **argv;
  int argc;

  char **dictionary;
  char *compressed_data;
  node_t *huff_tree;
};

// Input
bool has_valid_input(int argc, char **argv);
char *merge_input(int argc, char **argv);

// Compress
void compress_data(aux_t *aux);

#endif // SRC_ENCODER_ENCODER_H_
