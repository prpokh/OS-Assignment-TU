#include <unistd.h>
#include <fcntl.h>

int main() {
    int file_desc;

    file_desc = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);

    if (file_desc < 0) {
        write(1, "Error opening file\n", 19);
        return 1;
    }

    write(file_desc, "System Programming\n", 19);

    close(file_desc);

    write(1, "Task completed successfully\n", 28);

    return 0;
}