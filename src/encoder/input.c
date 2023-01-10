#include "encoder.h"

static int args_len(char **argv) {
  int size = 0;

  for (int i = 0; argv[i] != NULL; i++) {
    size += strlen(argv[i]);
  }
  return size;
}

static char *reduce_args(char **argv) {
  int total_length = args_len(argv);
  char *reduced_str = malloc(sizeof(char) * (total_length + 1));

  if (reduced_str == NULL) {
    perror("malloc");
    return NULL;
  }
  reduced_str[0] = '\0';
  for (int i = 0; argv[i] != NULL; i++) {
    strcat(reduced_str, argv[i]);
  }
  return reduced_str;
}

char *merge_input(int argc, char **argv) {
  if (argc == 2) {
    return argv[1];
  } else {
    return reduce_args(&argv[1]);
  }
}

static bool has_valid_argc(int argc) { return argc >= 2; }

bool has_valid_input(int argc, char **argv) { return has_valid_argc(argc); }
