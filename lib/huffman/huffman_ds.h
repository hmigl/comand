#ifndef LIB_HUFFMAN_HUFFMAN_DS_H_
#define LIB_HUFFMAN_HUFFMAN_DS_H_

#define FREQ_TABLE_SIZE 256

#include <stdlib.h>
#include <string.h>

typedef struct node node_t;
struct node {
  unsigned char c;
  size_t freq;
  struct node *next;
  struct node *left;
  struct node *right;
};

typedef struct list list_t;
struct list {
  node_t *head;
  size_t size;
};

/**
 * @brief Create frequency table from string
 *
 * @param str string - should not be empty
 * @return linked list storing all 'frequency nodes' created from 'str'
 */
list_t *new_freq_table(const char *str);

/**
 * @brief Create a binary-tree based on 'Huffman coding'
 *
 * @param list linked list storing 'frequency nodes'
 * @return the head of 'list'
 */
node_t *new_huff_tree(list_t *list);

/**
 * @brief Calculate a binary-tree's height
 *
 * @param head the head of the binary-tree
 * @return the binary-tree height
 */
int huff_tree_height(node_t *head);

/**
 * @brief Assemble a dictionary using the contents of the binary-tree nodes
 *
 * @param dic dictionary to be assmbled
 * @param head head of binary-tree
 * @param char_code string used to form a dictionary row
 * @param col max size of a dictionary column
 */
void assemble_dictionary(char **dic, node_t *head, char *char_code, int col);

/**
 * @brief Serialize a binary-tree into an int *
 *
 * @param root the binary-tree head
 * @param serialized_tree int * used to store the binary-tree nodes
 * @param index index to keep track of binary-tree nodes
 */
void serialize_tree(node_t *root, int *serialized_tree, int *index);

/**
 * @brief Deserialize an int * into a binary-tree
 *
 * @param serialized_tree serialized tree
 * @param index index to keep track of binary-tree nodes
 * @return deserialized binary-tree
 */
node_t *deserialize_tree(int *serialized_tree, int *index);

#endif // LIB_HUFFMAN_HUFFMAN_DS_H_
