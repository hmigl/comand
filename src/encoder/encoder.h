#ifndef SRC_ENCODER_ENCODER_H_
#define SRC_ENCODER_ENCODER_H_

#include "../../include/comand.h"

typedef struct aux aux_t;
struct aux {
  char **argv;
  int argc;

  unsigned int data_length;
  unsigned int encoded_data_length;
  unsigned int compressed_data_length;

  char **dictionary;
  char *encoded_data;
  unsigned char compressed_data[MAX_NODES];
  node_t *huff_tree;
};

/**
 * @brief Check if user input obeys the program contract
 *
 * @param argc argument counter
 * @param argv argument vector
 * @return true if no issues were found. Returns false otherwise
 */
bool has_valid_input(int argc, char **argv);

/**
 * @brief If 'argc' is greater than two, it will concat all arguments into a
 * single string
 *
 * @param argc argument counter
 * @param argv argument vector
 * @return 'argv[1]' if 'argc' == 2. Returns single string with all arguments
 * otherwise
 */
char *merge_input(int argc, char **argv);

/**
 * @brief Read 'file_name' contents writing they in a single string and
 * returning it
 *
 * @param file_name existing file path
 * @return string containg the contents of 'file_name'
 */
char *file_to_str(const char *file_name);

/**
 * @brief Uses bitshifting operations to compress data, writing relevant
 * information into 'aux'
 *
 * @param aux pointer to struct encapsulating all relevant data
 */
void compress_data(aux_t *aux);

#endif // SRC_ENCODER_ENCODER_H_
