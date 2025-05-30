#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
static int semid, msgid, shmid;
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
};
static struct sembuf up2 = {0, 2, 0};
static struct sembuf down = {0, -1, 0};
static struct sembuf zero = {0, 0, 0};

void create(char *forkey) {
    key_t key = ftok(forkey, 1);

    semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL);
    // msgid = msgget(key, 0666 | IPC_CREAT);
    // shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    union semun arg;
    arg.val = 0;
    semctl(semid, 0, SETVAL, arg);
}
void child(int type, char *forkey, int number) {
    key_t key = ftok(forkey, 1);
    semget(key, 1, 0666 | IPC_CREAT);
    if (type)
        for (int i = 1; i < number; i += 2) {
            semop(semid, &up2, 1);
            semop(semid, &zero, 1);
            printf("%d ", i);
        }
    else
        for (int i = 0; i < number; i += 2) {
            semop(semid, &down, 1);
            printf("%d ", i);
            semop(semid, &down, 1);
        }
    exit(0);
}
void delete(void) {
    semctl(semid, 0, IPC_RMID);
    semctl(semid, 1, IPC_RMID);
    msgctl(msgid, IPC_RMID, NULL);
    shmctl(shmid, IPC_RMID, NULL);
}
void handler(int sig) {
    exit(0);
}
int main(int argc, char *argv[]) {
    signal(SIGINT, handler);
    atexit(delete);

    create(argv[0]);

    int N;
    scanf("%d", &N);

    if (fork() == 0)
        child(1, argv[0], N);

    if (fork() == 0)
        child(0, argv[0], N);

    while(wait(NULL) != -1);

    return 0;
}