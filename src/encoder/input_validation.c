#include "encoder.h"

static bool can_read_file(char *filename) {
  if (access(filename, R_OK) < 0) {
    fprintf(stderr, "'%s': %s\n", filename, strerror(errno));
    return false;
  }
  return true;
}

static bool check_file_flag(int argc, char **argv) {
  if (argc == 3) {
    return !strcmp("--file", argv[1]) && can_read_file(argv[2]);
  }
  return true;
}

static bool has_valid_argc(int argc) { return argc == 2 || argc == 3; }

bool has_valid_input(int argc, char **argv) {
  return has_valid_argc(argc) && check_file_flag(argc, argv);
}
