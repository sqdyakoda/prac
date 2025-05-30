#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        argv[argc - 1] = NULL;
        execvp(argv[1], &argv[1]);
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                pid_t pid2 = fork();
                if (pid2 == 0) {
                    execlp(argv[argc - 1], argv[argc - 1], NULL);
                    exit(1);
                } else {
                    waitpid(pid2, &status, 0);
                }
            }
        }
    }
    return 0;
}