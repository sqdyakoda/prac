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
// union semun {
//     int val;
//     struct semid_ds *buf;
//     unsigned short  *array;
//     struct seminfo  *__buf;
// };
void create(char *forkey) {
    key_t key = ftok(forkey, 1);

    semid = semget(key, 2, 0666 | IPC_CREAT);
    msgid = msgget(key, 0666 | IPC_CREAT);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    semctl(semid, 0, SETVAL, 0);
    semctl(semid, 1, SETVAL, 0);
}
void child(char *forkey) {
    key_t key = ftok(forkey, 1);

    semget(key, 0, 0666);
    msgget(key, 0666);
    shmget(key, 0, 0666);

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

    if (fork() == 0)
        child(argv[0]);
    
    wait(NULL);
    return 0;
}