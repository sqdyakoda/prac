// #include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        exit(1);
    int fd;
    if ((fd = open(argv[2], O_RDONLY)) == -1)
        exit(1);
    pid_t pid = fork();
    if (pid == 0) {
        dup2(fd, 0);
        close(fd);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    } else
        wait(NULL);
    return 0;
}