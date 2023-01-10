#include "c_ipc.h"

static int get_block(const char *pathname, int size) {
  key_t key = ftok(pathname, 'h');

  if (key == -1) {
    perror("ftok");
    return -1;
  }

  return shmget(key, size, 0666 | IPC_CREAT);
}

void *map_block(char *pathname, size_t size) {
  int block_id = get_block(pathname, size);
  void *block_addr;

  if (block_id == -1) {
    perror("shmget");
    return NULL;
  }

  block_addr = shmat(block_id, NULL, 0);
  if (block_addr == (void *)-1) {
    perror("shmat");
    return NULL;
  }

  return block_addr;
}

int detach_block(void *block) { return shmdt(block); }

int erase_block(char *pathname) {
  int block_id = get_block(pathname, 0);

  if (block_id == -1) {
    perror("shmget");
    return -1;
  }

  return shmctl(block_id, IPC_RMID, NULL);
}
