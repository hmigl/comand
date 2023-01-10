#ifndef LIB_COMAND_IPC_C_IPC_H_
#define LIB_COMAND_IPC_C_IPC_H_

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct comand_ipc_data data_t;
struct comand_ipc_data {
  char *data;
  unsigned long total_bytes;
  // unsigned long total_compressed_bytes;
  // unsigned long time_to_decompress;
};

#endif // LIB_COMAND_IPC_C_IPC_H_
