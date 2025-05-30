#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

static int shmid, semid, *shmaddr;

static struct sembuf UP2 = {0, 2, 0};
static struct sembuf DOWN1 = {0, -1, 0};
static struct sembuf ZERO = {0, 0, 0};

union semun {
    int val; 
    struct semid_ds *buf; 
    unsigned short  *array; 
    struct seminfo  *__buf; 
};

void create(char* for_key, int n) {
    //так как вызывается в отце, то тут же и заполняется память
    key_t key = ftok(for_key, 1);

    semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL);

    union semun arg;
    arg.val = 0;
    //иницаилизация семафора начальным значением = 0
    semctl(semid, 0, SETVAL, arg);

    //в отце создали разд. память, подсоединяет область разделяемой памяти 
    //к вирт.адр. пространству отца
    shmid = shmget(key, n * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL);
    shmaddr = (int *)shmat(shmid, 0, 0);
    
    //что тут происходит? почему мы так делаем?
    for (int i = 0; i < n; ++i) {
        shmaddr[i] = i; 
    }

}

void child(char* for_key, int n, int type) {
    key_t key = ftok(for_key, 1);

    //получили доступ к семафору(1 в массиве)
    int sem = semget(key, 1, 0666 | IPC_CREAT);

    if (type == 1) {
        for (int i = 0; i < n / 2; ++i) {
            semop(sem, &UP2, 1);
            semop(sem, &ZERO, 1);
            shmaddr[i] += 1;
        }
    }

    if (type == 2) {
        for (int i = n - 1; i >= n / 2; --i) {
            semop(sem, &DOWN1, 1);
            shmaddr[i] += 1;
            semop(sem, &DOWN1, 1);
        }
    }

    //разделяемую память открепили
    // shmdt(shmaddr);
}

void cleanIPC(void) {
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, NULL);
}

void handler(int sig) {
    exit(0);
}

int main(int argc, char* argv[]) {
    int N;
    scanf("%d", &N);
    setbuf(stdout, 0);

    if (N >= 100000) 
        return 0;

    signal(SIGINT, handler);
    atexit(cleanIPC);
    create(argv[0], N);

    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        child(argv[0], N, 1);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        child(argv[0], N, 2);
        exit(0);
    }

    while(wait(NULL) != -1);

    if (N <= 50000) {
        for (int i = 0; i < N; i++) {
            printf("%d ", shmaddr[i]);
        }
        printf("\n");
    }

    return 0;
}