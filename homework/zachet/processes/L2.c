// #include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    int fd[2], status, status2;
    pid_t pid1, pid2, pid3, pid4;
    pipe(fd);
    if ((pid1 = fork()) == 0) {
        // (p1 || p2)
        // p1
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        if ((pid2 = fork()) == 0) {
            
            execlp(argv[1], argv[1], NULL);
            return 127;
        }
        waitpid(pid2, &status, 0);
        if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
            // p2
            if ((pid3 = fork()) == 0) {
                execlp(argv[2], argv[2], NULL);
                return 127;
            }
            waitpid(pid3, NULL, 0);
        }
        return 0;
    }
    if ((pid4 = fork()) == 0) {
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);
        execvp(argv[3], argv + 3);
        return 127;
    }
    close(fd[1]);
    close(fd[0]);

    waitpid(pid4, &status2, 0);
    while(wait(NULL) != -1);
    
    return WIFEXITED(status2) ? WEXITSTATUS(status2) : 128 + WTERMSIG(status2);
}