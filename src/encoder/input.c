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

static void read_into_buffer(FILE *file, unsigned char *contents, long size) {
  int bytes_read = fread(contents, sizeof(char), size, file);

  if (bytes_read != size) {
    perror("fread");
    exit(1);
  }
  contents[size] = '\0';
}

static long get_file_size(FILE *file) {
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);
  return size;
}

static FILE *open_file(const char *file_name) {
  FILE *file = fopen(file_name, "r");

  if (file == NULL) {
    perror("fopen");
    exit(1);
  }
  return file;
}

unsigned char *file_to_str(const char *file_name) {
  FILE *file = open_file(file_name);
  long size = get_file_size(file);
  unsigned char *contents = malloc(size + 1);

  if (contents == NULL) {
    perror("malloc");
    exit(1);
  }
  read_into_buffer(file, contents, size);
  fclose(file);
  return contents;
}
