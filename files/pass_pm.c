#include <stdio.h>
#include <pthread.h>

void* display_val(void* arg) {
    int received = *(int*)arg;

    printf("Value in thread: %d\n", received);

    return NULL;
}

int main() {
    pthread_t thread_id;
    int my_number = 55;

    pthread_create(&thread_id, NULL, display_val, &my_number);

    pthread_join(thread_id, NULL);

    return 0;
}