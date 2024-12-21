#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h> 
#include <sys/msg.h> 
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <signal.h>
#include <string.h>

static int semaphore;

static struct sembuf P0 = {.sem_op = 0};
static struct sembuf V2 = {.sem_op = 2};
static struct sembuf P1 = {.sem_op = -1};

void cleanUp(void){
    semctl(semaphore, 0, IPC_RMID);
}

void son(char* str, int type, int N){
    key_t key = ftok(str, 1);
    semget(key, 1, IPC_CREAT | 0666);
    if (type == 0)
    {
        for (int i = 0; i < N; i+=2)
        {
            semop(semaphore, &P0, 1);
            printf("%d\n", i);
            semop(semaphore, &V2, 1);
        }
    }
    else {
        for (int i = 1; i < N; i+=2)
        {
            semop(semaphore, &P1, 1);
            printf("%d\n", i);
            semop(semaphore, &P1, 1);
        }
    }
}

int main(int argc, char*argv[]){
    setbuf(stdout, 0);
    key_t key = ftok(argv[0], 1);
    semaphore = semget(key, 1, IPC_CREAT | 0666);
    semctl(semaphore, 0, SETVAL, (int)0);
    pid_t pid_1 = -1, pid_2 = -1;
    int N = 0;

    atexit(cleanUp);

    scanf("%d", &N);

    if((pid_1 = fork()) == 0){ // четные 
        son(argv[0], 0, N);
        exit(0);
    }

    if((pid_2 = fork()) == 0){ // нечетные
        son(argv[0], 1, N);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    return EXIT_SUCCESS;
}