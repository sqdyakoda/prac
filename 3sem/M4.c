#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
typedef void (*pHandler) (int);
static int flag1 = 0;
static int flag2 = 0;
int num = 0;
void handler1(int sig) {
    flag1 = 1;
}
void handler2(int sig) {
    flag2 = 1;
}
void update_file(int fd) {
    lseek(fd, SEEK_SET, 0);
    read(fd, &num, sizeof(int));
    num++;
    lseek(fd, SEEK_SET, 0);
    write(fd, &num, sizeof(int));
    close(fd);
}
void ad(void) {
    num++;
}
int main(void) {
    signal (SIGUSR1, handler1);
    signal (SIGUSR2, handler2);
    char tmp[] = "tmpXXXXXX";
    int fd = mkstemp(tmp);
    unlink(tmp);
    int n;
    write(fd, &num, 4);
    pid_t array[50];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        if ((array[i] = fork()) == 0) {
            while(flag1 == 0)
                usleep(1000);
            update_file(fd);
            flag1 = 0;
            kill(getppid(), SIGUSR2);
            exit(0);
        }
    }
    usleep(1000);
    for (int i = 0; i < n; ++i) {
        kill(array[i], SIGUSR1);
        while (flag2 == 0)
            usleep(1000);
        flag2 = 0;
    }
    lseek(fd, SEEK_SET, 0);
    read(fd, &num, 4);
    printf("%d\n", num);
    while(wait(NULL) != -1);
    close(fd);
    return 0;
}