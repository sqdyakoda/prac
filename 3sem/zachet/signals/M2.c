#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
typedef void (*pHandler) (int);
static int flag = 1;
void onint(int sig) {
    if (flag) {
        //если с последнего print(Hi!) успела пройти секунда
        flag = 0;
        alarm(1);
        printf("Hi!\n");
    } else {
        printf("Bye-bye!\n");
        exit(0);
    }
}
void onalrm(int sig) {
    flag = 1;
}
int main(void) {
    signal(SIGINT, onint);
    signal(SIGALRM, onalrm);
    // alarm(1);
    while(1)
        pause();
    return 0;
}

