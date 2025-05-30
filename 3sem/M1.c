#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
typedef void (*pHandler) (int);
void handler(int sig) {
    static int count = 0;
    count++;
    printf("%d\n", count);
    if (count >= 5)
        exit(0);
}
int main(void) {
    pid_t pid;
    signal(SIGINT, handler);
    if ((pid = fork()) == 0) {
        while (1)
            pause();
    } else {
        usleep(500);
        for (int i = 0; i < 5; ++i) {
            kill(pid, SIGINT);
            usleep(500);
        }
        wait(NULL);
    }
    return 0;
}