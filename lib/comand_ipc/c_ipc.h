#ifndef LIB_COMAND_IPC_C_IPC_H_
#define LIB_COMAND_IPC_C_IPC_H_

#define PATHNAME "Makefile"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/**
 * @brief Map a shared memory block into a program's address space and returns
 * it
 *
 * @param pathname file to be associated with the shared memory segment
 * @param size the size of the shared memory segment
 * @return a pointer to the mapped block
 */
void *map_block(char *pathname, size_t size);

/**
 * @brief Detache the shared memory segment
 *
 * @param block shared memory segment to be detached
 * @return upon successful completion returns 0. -1 is returned otherwise
 */
int detach_block(void *block);

/**
 * @brief Get rid of a shared memory segment
 *
 * @param pathname file associated with the shared memory segment
 * @return upon successful completion returns 0. -1 is returned otherwise
 */
int erase_block(char *pathname);

#endif // LIB_COMAND_IPC_C_IPC_H_
