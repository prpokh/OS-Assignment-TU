#include <stdio.h>
#include <pthread.h>

int shared_total = 0;

void* add_task(void* arg) {
    for(int j = 0; j < 50000; j++) {
        shared_total++;
    }
    return NULL;
}

void* sub_task(void* arg) {
    for(int j = 0; j < 50000; j++) {
        shared_total--;
    }
    return NULL;
}

int main() {
    pthread_t thread_a, thread_b;

    pthread_create(&thread_a, NULL, add_task, NULL);
    pthread_create(&thread_b, NULL, sub_task, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    printf("Resulting value: %d\n", shared_total);

    return 0;
}