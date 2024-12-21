#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
typedef void (*pHandler) (int);
static int p1_flag = 0;
static int p2_flag = 0;
void handler1(int sig) {
    p2_flag = 1;
}
void handler2(int sig) {
    p1_flag = 1;
}
int main(void) {
    setbuf(stdout, 0);
    signal(SIGUSR1, handler1);
    signal(SIGUSR2, handler2);
    int N;
    scanf("%d", &N);
    pid_t pid;
    if ((pid = fork()) == 0) {
        for (int i = 1; i <= N; ++i) {
            kill(getppid(), SIGUSR1);
            while(p1_flag == 0)
                usleep(1000);
            printf("%d\n", i);
            p1_flag = 0;
        }
    } else {
        for (int j = 1; j <= N; ++j) {
            while (p2_flag == 0)
                usleep(1000);
            printf("%d\n", j);
            p2_flag = 0;
            kill(pid, SIGUSR2);
        }
    }
    while (wait(NULL) != -1);
    return 0;
}