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

list_t *new_freq_table(const char *str);
node_t *new_huff_tree(list_t *list);
int huff_tree_height(node_t *head);
void assemble_dictionary(char **dic, node_t *head, char *char_code, int col);

#endif // LIB_HUFFMAN_HUFFMAN_DS_H_
