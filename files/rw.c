#include <unistd.h>
#include <fcntl.h>

int main() {
    char data[80];
    
    write(1, "Input text: ", 12);
    
    int bytes = read(0, data, 80);
    
    write(1, "Output: ", 8);
    write(1, data, bytes);
    
    return 0;
}