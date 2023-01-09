#ifndef SRC_ENCODER_ENCODER_H_
# define SRC_ENCODER_ENCODER_H_

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

// Validation
bool has_valid_input(int argc, char **argv);

#endif  // SRC_ENCODER_ENCODER_H_
