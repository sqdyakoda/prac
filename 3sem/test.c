#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == 0) {

        execvp(argv[1], &argv[1], NULL);
        perror("lalala");
        exit(1);
    } else {
        wait(NULL);
    }
    return 0;
}