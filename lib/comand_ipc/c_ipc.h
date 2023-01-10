#ifndef LIB_COMAND_IPC_C_IPC_H_
#define LIB_COMAND_IPC_C_IPC_H_

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

void *map_block(char *pathname, size_t size);

#endif // LIB_COMAND_IPC_C_IPC_H_
