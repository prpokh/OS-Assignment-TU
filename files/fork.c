#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t process_id;

    process_id = fork();

    if (process_id < 0) {
        printf("Error: Forking failed\n");
        return 1;
    }
    else if (process_id == 0) {
        printf("Current: Child Process\n");
        printf("ID: %d\n", getpid());
    }
    else {
        printf("Current: Parent Process\n");
        printf("Parent ID: %d\n", getpid());
        printf("Child ID created: %d\n", process_id);
    }

    return 0;
} 