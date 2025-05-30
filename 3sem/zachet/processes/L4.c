#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
int main(void) {
    pid_t pid1, pid2, pid3;
    char c, c2;
    int fd[2], flag = 0, flag2 = 0;
    pipe(fd);
    if ((pid1 = fork()) == 0) {
        close(fd[0]);
        while (read(0, &c, 1)) {
            if (flag) {
                flag = 0;
                write(fd[1], &c, 1);
            } else {
                flag = 1;
            }
        }
        close(fd[1]);
        return 0;
    }
    close(fd[1]);
    if ((pid2 = fork()) == 0) {
        if ((pid3 = fork()) == 0) {
            while (read(fd[0], &c2, 1)) {
                if (flag2) {
                    flag2 = 0;
                    write(1, &c2, 1);
                } else {
                    flag2 = 1;
                }
            }
            close(fd[0]);
            return 0;
        }
        close(fd[0]);
        waitpid(pid3, NULL, 0);
        return 0;
    }
    close(fd[0]);
    while (wait(NULL) != -1);
    return 0;
}