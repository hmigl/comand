#ifndef SRC_ENCODER_ENCODER_H_
#define SRC_ENCODER_ENCODER_H_

#include "c_ipc.h"
#include "huffman_ds.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Input
bool has_valid_input(int argc, char **argv);
char *merge_input(int argc, char **argv);

// Compress
void compress_data(int argc, char **argv);

#endif // SRC_ENCODER_ENCODER_H_
