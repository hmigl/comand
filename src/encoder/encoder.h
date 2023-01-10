#ifndef SRC_ENCODER_ENCODER_H_
#define SRC_ENCODER_ENCODER_H_

#include "c_ipc.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Validation
bool has_valid_input(int argc, char **argv);

#endif // SRC_ENCODER_ENCODER_H_
