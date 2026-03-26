#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *worker_logic(void *arg);

int x, y;

int main() {
    pthread_t my_tid;

    pthread_create(&my_tid, NULL, worker_logic, NULL);

    pthread_join(my_tid, NULL);

    printf("Main execution started\n");

    for(y = 50; y < 55; y++) {
        printf("%d\n", y);
        sleep(1);
    }

    return 0;
}

void *worker_logic(void *arg) {
    printf("Thread execution started\n");

    for(x = 10; x < 15; x++) {
        printf("%d\n", x);
        sleep(1);
    }

    return NULL;
}