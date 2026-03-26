#include <stdio.h>
#include <pthread.h>

int shared_data = 0;
pthread_mutex_t m_lock;

void* task_up(void* arg) {
    for(int n = 0; n < 120000; n++) {
        pthread_mutex_lock(&m_lock);
        shared_data++;
        pthread_mutex_unlock(&m_lock);
    }
    return NULL;
}

void* task_down(void* arg) {
    for(int n = 0; n < 120000; n++) {
        pthread_mutex_lock(&m_lock);
        shared_data--;
        pthread_mutex_unlock(&m_lock);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&m_lock, NULL);

    pthread_t thread_1, thread_2;
    
    pthread_create(&thread_1, NULL, task_up, NULL);
    pthread_create(&thread_2, NULL, task_down, NULL);
    
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("Final total: %d\n", shared_data);

    pthread_mutex_destroy(&m_lock);
    return 0;
}