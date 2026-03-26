#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL_GUESTS 6
#define THINK_TIME 1
#define EAT_TIME 1

sem_t fork_locks[TOTAL_GUESTS]; 

void* execute_dining_cycle(void* arg)
{
    int guest_id = *(int*)arg;
    int left_fork = guest_id;
    int right_fork = (guest_id + 1) % TOTAL_GUESTS;

    printf("Guest %d is pondering life...\n", guest_id);
    sleep(THINK_TIME);

    // Deadlock Prevention: The "Asymmetric" approach
    // If guest_id is the last one, they grab the right fork first.
    if (guest_id == TOTAL_GUESTS - 1) 
    {
        sem_wait(&fork_locks[right_fork]);
        printf("Guest %d secured fork %d (Right)\n", guest_id, right_fork);

        sem_wait(&fork_locks[left_fork]);
        printf("Guest %d secured fork %d (Left)\n", guest_id, left_fork);
    } 
    else 
    {
        sem_wait(&fork_locks[left_fork]);
        printf("Guest %d secured fork %d (Left)\n", guest_id, left_fork);

        sem_wait(&fork_locks[right_fork]);
        printf("Guest %d secured fork %d (Right)\n", guest_id, right_fork);
    }

    // Critical Section: Eating
    printf("Guest %d is currently eating.\n", guest_id);
    sleep(EAT_TIME);

    // Release resources
    sem_post(&fork_locks[left_fork]);
    sem_post(&fork_locks[right_fork]);

    printf("Guest %d finished eating and released forks %d & %d.\n", guest_id, left_fork, right_fork);

    return NULL;
}

int main() 
{
    pthread_t guest_threads[TOTAL_GUESTS];
    int guest_indices[TOTAL_GUESTS];

    // Initialize semaphores
    for (int i = 0; i < TOTAL_GUESTS; i++) {
        sem_init(&fork_locks[i], 0, 1);
    }

    // Launch threads
    for (int i = 0; i < TOTAL_GUESTS; i++) {
        guest_indices[i] = i;
        if (pthread_create(&guest_threads[i], NULL, execute_dining_cycle, &guest_indices[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    // Synchronize threads
    for (int i = 0; i < TOTAL_GUESTS; i++) {
        pthread_join(guest_threads[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < TOTAL_GUESTS; i++) {
        sem_destroy(&fork_locks[i]);
    }

    printf("Dining session complete.\n");
    return 0;
}