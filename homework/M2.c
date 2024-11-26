#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
typedef void (*pHandler) (int);
static int count = 0;
void onint(int sig) {
    ++count;
    printf("Hi!\n");
}
void onalrm(int sig) {
    if (count > 1) {
        printf("Bye-bye!\n");
        exit(0);
    }
    count = 0;
    alarm(1);
}
int main(void) {
    signal(SIGINT, onint);
    signal(SIGALRM, onalrm);
    alarm(1);
    while(1)
        pause();
    return 0;
}