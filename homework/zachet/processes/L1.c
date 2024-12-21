// #include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    int index = -1, status, fd[2];
    pid_t pid1, pid2;
    for (int i = 0; i < argc; ++i)
        if (strcmp(argv[i], "--") == 0) {
            argv[i] = NULL;
            index = i;
        }
    pipe(fd);
    if ((pid1 = fork()) == 0) {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        execvp(argv[1], argv + 1);
        return 127;
    } else if ((pid2 = fork()) == 0) {
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);
        execvp(argv[index + 1], argv + index + 1);
        return 127;
    }
    close(fd[1]);
    close(fd[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status);
}