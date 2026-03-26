#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int global_val = 0;
sem_t my_sem;

void* plus_op(void* arg) {
    for(int k = 0; k < 75000; k++) {
        sem_wait(&my_sem);
        global_val++;
        sem_post(&my_sem);
    }
    return NULL;
}

void* minus_op(void* arg) {
    for(int k = 0; k < 75000; k++) {
        sem_wait(&my_sem);
        global_val--;
        sem_post(&my_sem);
    }
    return NULL;
}

int main() {
    sem_init(&my_sem, 0, 1);

    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, plus_op, NULL);
    pthread_create(&thread2, NULL, minus_op, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Total: %d\n", global_val);

    sem_destroy(&my_sem);
    return 0;
}