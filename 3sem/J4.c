#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(argv[1], &argv[1]);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("%d\n", WTERMSIG(status));
        }
    }
    return 0;
}