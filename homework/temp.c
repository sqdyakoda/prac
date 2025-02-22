#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int flag = 0;
static int count_0 = 0;
static int execute = 0;
//static int flag2 = 0;

void s1(int sig) {
    //flag = 1;//теперь выполняем всё, что после while(!flag)
    //++flag2;
    ++flag;
        //printf("s1\n");
}
void s2(int sig) {
    while ((execute != 0) || (flag != 0)/* || (flag2 != 0)*/) {
        usleep(1000);
        //printf("ext = %d\n", execute);
    }
        
    //printf("END OF SON\n");
    exit(0);
}

int main(int argc, char* argv[]) {    
    setbuf(stdout, NULL);
    signal(SIGUSR1, s1);
    signal(SIGTERM, s2);

    pid_t pid;
    if ((pid = fork()) == 0) {
        while (1) {
            while (!flag) {
                usleep(1000);
                //printf("SON_CYCLE\n");
            }
            ++count_0;
            if ((count_0 % 3) == 0)
                ++execute;
            if (execute > 0) {
                //printf("AAA\n");
                pid_t pid1, pid2;
                int i = 1, fd[2];
                pipe(fd);
                while (i < argc) {
                    if (strcmp(argv[i], "--") == 0)
                        break;
                    ++i;
                }
                //printf("AAA\n");
                if ((pid1 = fork()) == 0) {//p1
                    dup2(fd[1], 1);
                    close(fd[0]);
                    close(fd[1]);
                    argv[i] = NULL;
                    execvp(argv[1], &argv[1]);
                    exit(127);
                }
                if ((pid2 = fork()) == 0) {//p2
                    dup2(fd[0], 0);
                    close(fd[0]);
                    close(fd[1]);
                    execvp(argv[i+1], &argv[i+1]);
                    exit(127);
                }
                close(fd[0]);
                close(fd[1]);
                // while (wait(NULL) != -1);
                waitpid(pid1, NULL, 0);
                waitpid(pid2, NULL, 0);
                --execute;
            }
            //--flag2;
            --flag;
        }
    }
    unsigned n;
    while (scanf("%u", &n) != -1) {
        if (n)
            usleep(n);
        else {
            kill(pid, SIGUSR1);
            //usleep(1000);
        }
        //printf("FATHER_CYCLE\n");
        //if (waitpid(pid, &status, 0) == -1)
        //    return 0;
    }

    //printf("A\n");
    
    kill(pid, SIGTERM);
    while (wait(NULL) != -1);
    return 0;
}