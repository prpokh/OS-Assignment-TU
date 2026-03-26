#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_p;

    child_p = fork();

    if (child_p < 0) {
        printf("Error: Fork failed\n");
        return 1;
    }
    else if (child_p == 0) {
        printf("Child starts execution\n");
        sleep(2);
        printf("Child execution done\n");
    }
    else {
        wait(NULL);
        printf("Parent resumed after child\n");
    }

    return 0;
}