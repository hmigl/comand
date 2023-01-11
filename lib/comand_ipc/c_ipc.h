#ifndef LIB_COMAND_IPC_C_IPC_H_
#define LIB_COMAND_IPC_C_IPC_H_

#define PATHNAME "Makefile"
#define BLOCK_SIZE sizeof(struct comand_ipc_data)
#define SIZE 256

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct comand_ipc_data data_t;
struct comand_ipc_data {
  // char *data;
  char data[SIZE];
  unsigned long total_bytes;
  // unsigned long total_compressed_bytes;
  // unsigned long time_to_decompress;
};

void *map_block(char *pathname, size_t size);
int detach_block(void *block);
int erase_block(char *pathname);

#endif // LIB_COMAND_IPC_C_IPC_H_
