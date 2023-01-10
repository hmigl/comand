#include "encoder.h"

static void display_usage(void) {
  fprintf(stderr, "Usage: ./encoder [TEXT]...\n");
}

int main(int argc, char **argv) {
  data_t data;

  if (!has_valid_input(argc, argv)) {
    display_usage();
    return 1;
  }
  data = (data_t){.data = merge_input(argc, argv)};
  printf("%s\n", data.data);
  return 0;
}
