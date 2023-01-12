#ifndef LIB_COMAND_IPC_C_IPC_H_
#define LIB_COMAND_IPC_C_IPC_H_

#define PATHNAME "Makefile"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct comand_ipc_data data_t;
struct comand_ipc_data {
  size_t data_length;
  char dictionary[256][256];
  char data[];
};

void *map_block(char *pathname, size_t size);
int detach_block(void *block);
int erase_block(char *pathname);

#endif // LIB_COMAND_IPC_C_IPC_H_
