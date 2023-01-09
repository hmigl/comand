#include "encoder.h"

static void display_usage(void) {
  fprintf(stderr, "Usage: ./encoder [TEXT]...\n");
}

int main(int argc, char **argv) {
  if (!has_valid_input(argc, argv)) {
    display_usage();
    return 1;
  }
  return 0;
}
