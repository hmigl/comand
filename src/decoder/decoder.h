#ifndef SRC_DECODER_DECODER_H_
#define SRC_DECODER_DECODER_H_

#include "../../include/comand.h"

/**
 * @brief Use 'Huffman Coding' to decompress a compressed string
 *
 * @param huff_tree binary-tree used to re-create the original string
 * @param block pointer to struct encapsulating all relevant data
 */
void decompress(node_t *huff_tree, data_t *block);

#endif // SRC_DECODER_DECODER_H_
