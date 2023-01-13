#include "huffman_ds.h"

static void lst_add_sorted(list_t *list, node_t *node) {
  node_t *tmp;

  if (list->head == NULL) {
    list->head = node;
  } else if (node->freq < list->head->freq) {
    node->next = list->head;
    list->head = node;
  } else {
    tmp = list->head;
    while (tmp->next != NULL && tmp->next->freq <= node->freq) {
      tmp = tmp->next;
    }
    node->next = tmp->next;
    tmp->next = node;
  }
  list->size++;
}

static list_t *trim_freq_table(unsigned int *freq_table) {
  list_t *list = malloc(sizeof(list_t));

  list->head = NULL;
  list->size = 0;
  for (unsigned int i = 0; i < FREQ_TABLE_SIZE; i++) {
    if (freq_table[i] > 0) {
      node_t *node = malloc(sizeof(node_t));
      node->c = i;
      node->freq = freq_table[i];
      node->next = NULL;
      node->left = NULL;
      node->right = NULL;
      lst_add_sorted(list, node);
    }
  }
  return list;
}

list_t *new_freq_table(const char *str) {
  unsigned int freq[FREQ_TABLE_SIZE] = {0};

  for (size_t i = 0; i < strlen(str); i++) {
    freq[(unsigned char)str[i]]++;
  }
  return trim_freq_table(freq);
}

static node_t *lst_rm_head(list_t *list) {
  node_t *tmp = NULL;

  if (list->head == NULL)
    return NULL;
  tmp = list->head;
  list->head = tmp->next;
  tmp->next = NULL;
  list->size--;
  return tmp;
}

int huff_tree_height(node_t *head) {
  int left, right;

  if (head == NULL) {
    return -1;
  }
  left = huff_tree_height(head->left) + 1;
  right = huff_tree_height(head->right) + 1;
  return left > right ? left : right;
}

node_t *new_huff_tree(list_t *list) {
  node_t *first, *second, *new_combined_node;

  while (list->size > 1) {
    first = lst_rm_head(list);
    second = lst_rm_head(list);
    new_combined_node = malloc(sizeof(node_t));
    new_combined_node->freq = first->freq + second->freq;
    new_combined_node->left = first;
    new_combined_node->right = second;
    new_combined_node->next = NULL;
    lst_add_sorted(list, new_combined_node);
  }
  return list->head;
}

static void copy_char_code(char *left, char *right, char *char_code) {
  strcpy(left, char_code);
  strcpy(right, char_code);
}

static void concat_char_code(char *left, char *right) {
  strcat(left, "0");
  strcat(right, "1");
}

void assemble_dictionary(char **dic, node_t *head, char *char_code, int col) {
  char left[col], right[col];

  if (head == NULL)
    return;
  if (head->left == NULL && head->right == NULL) {
    strcpy(dic[head->c], char_code); // TODO: improve
  } else {
    copy_char_code(left, right, char_code);
    concat_char_code(left, right);
    assemble_dictionary(dic, head->left, left, col);
    assemble_dictionary(dic, head->right, right, col);
  }
}

void serialize_tree(node_t *root, int *serialized_tree, int *index) {
  if (root != NULL) {
    serialized_tree[*index] = root->c;
    (*index)++;
    serialize_tree(root->left, serialized_tree, index);
    serialize_tree(root->right, serialized_tree, index);
  } else {
    serialized_tree[*index] = -1;
    (*index)++;
  }
}

node_t *deserialize_tree(int *serialized_tree, int *index) {
  if (serialized_tree[*index] == -1) {
    (*index)++;
    return NULL;
  }
  struct node *root = (struct node *)malloc(sizeof(struct node));
  root->c = (unsigned char)serialized_tree[*index];
  (*index)++;
  root->left = deserialize_tree(serialized_tree, index);
  root->right = deserialize_tree(serialized_tree, index);
  return root;
}
