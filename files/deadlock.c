#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Renamed shared resources
pthread_mutex_t printer_lock;
pthread_mutex_t scanner_lock;

// Function for the first worker
void* office_worker_A(void* arg)
{
    printf("[Worker A] Attempting to secure the Printer...\n");
    pthread_mutex_lock(&printer_lock);
    printf("[Worker A] Printer LOCKED.\n");

    // Hold the printer and wait, allowing Worker B to grab the scanner
    sleep(1); 

    printf("[Worker A] Now attempting to secure the Scanner...\n");
    pthread_mutex_lock(&scanner_lock); // DEADLOCK: Worker B has this
    
    printf("[Worker A] Success! Performing office tasks.\n");

    pthread_mutex_unlock(&scanner_lock);
    pthread_mutex_unlock(&printer_lock);

    return NULL;
}

// Function for the second worker
void* office_worker_B(void* arg)
{
    printf("[Worker B] Attempting to secure the Scanner...\n");
    pthread_mutex_lock(&scanner_lock);
    printf("[Worker B] Scanner LOCKED.\n");

    // Hold the scanner and wait, allowing Worker A to grab the printer
    sleep(1); 

    printf("[Worker B] Now attempting to secure the Printer...\n");
    pthread_mutex_lock(&printer_lock); // DEADLOCK: Worker A has this
    
    printf("[Worker B] Success! Performing office tasks.\n");

    pthread_mutex_unlock(&printer_lock);
    pthread_mutex_unlock(&scanner_lock);

    return NULL;
}

int main()
{
    pthread_t thread_A, thread_B;

    // Initialize the mutexes
    pthread_mutex_init(&printer_lock, NULL);
    pthread_mutex_init(&scanner_lock, NULL);

    printf("Starting Office Simulation: Expecting Circular Wait Deadlock...\n\n");

    pthread_create(&thread_A, NULL, office_worker_A, NULL);
    pthread_create(&thread_B, NULL, office_worker_B, NULL);

    // The program will hang here indefinitely
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    // Cleanup (Technically never reached in a deadlock)
    pthread_mutex_destroy(&printer_lock);
    pthread_mutex_destroy(&scanner_lock);

    return 0;
}