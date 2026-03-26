// sender program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    void *shm_ptr;
    int mem_id;

    mem_id = shmget((key_t)5566, 2048, 0666 | IPC_CREAT);

    printf("ID of allocated memory: %d\n", mem_id);

    shm_ptr = shmat(mem_id, NULL, 0);

    printf("Process attached at address: %p\n", shm_ptr);

    printf("Write a message: ");
    fgets((char *)shm_ptr, 2048, stdin);

    printf("Data stored in memory: %s\n", (char *)shm_ptr);

    shmdt(shm_ptr);

    return 0;
}

// reciever program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    void *shm_ptr;
    int mem_id;

    mem_id = shmget((key_t)5566, 2048, 0666);

    printf("ID of allocated memory: %d\n", mem_id);

    shm_ptr = shmat(mem_id, NULL, 0);

    printf("Process attached at address: %p\n", shm_ptr);

    printf("Data fetched: %s\n", (char *)shm_ptr);

    shmdt(shm_ptr);

    shmctl(mem_id, IPC_RMID, NULL);

    printf("Cleanup completed.\n");

    return 0;
}