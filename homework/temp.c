#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
int main() {
    char str = 'a', s2;
    int fd = open("inputt.txt", O_RDWR | O_TRUNC);
    write(fd, &str, sizeof(char));
    lseek(fd, SEEK_SET, 0);


    read(fd, &s2, sizeof(char));
    printf("[%c]\n", s2);


    str = 'b';
    write(fd, &str, sizeof(char));
    read(fd, &s2, sizeof(char));
    printf("[%c]\n", s2);

    
    return 0;
}