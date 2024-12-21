#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void cclient(char* for_key, int n) {

    struct {
        long type;
        char mes[50];
    } Message_to;

    struct {
        long type;
        char mes[50];
    } Message_from;

    //функция для процесса-клиента
    key_t key = ftok(for_key, 1);
    int msqid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    // printf("Its in client%d\n", msqid);


    Message_to.type = 1; // 1 = увеличение числа
    strcpy(Message_to.mes, "");

    for (int i = 0; i < n; ++i) {
        msgsnd(msqid, &Message_to, sizeof(Message_to) - sizeof(Message_to.type), 0); //посылаем в очередь сообщения c номером 1
        // printf("Client sends UP\n");
    }

    Message_to.type = 2; // 2 = операция возврата числа
    msgsnd(msqid,  &Message_to, sizeof(Message_to) - sizeof(Message_to.type), 0);

    //теперь надо получить число и распечатать его на стандратный вывод
    //открываем ещё одну очередь, через которую получим число
    key_t key_getnum = ftok(for_key, 2);
    int msqid_getnum = msgget(key_getnum, 0666 | IPC_CREAT | IPC_EXCL);

    //получаем измененное число от сервера
    msgrcv(msqid_getnum, &Message_from, sizeof(Message_from) - sizeof(Message_from.type), 3, 0);
    // write(1, Message_from.mes, sizeof(Message_from.mes));
    // printf("%s\n <-- I got from server\n", Message_from.mes);
    printf("%s\n", Message_from.mes);
    // printf("@@@Client is about to finish!\n");

    msgctl(msqid_getnum, IPC_RMID, 0);
    msgctl(msqid, IPC_RMID, 0);

}

void sserver(char* for_key) {

    struct {
        long type;
        char mes[50];
    } Message_from;

    struct {
        long type;
        char mes[50];
    } Message_to;

    int changing_number = 0; //число, которое мы увеличиваем

    //функция для процесса-сервера
    key_t key = ftok(for_key, 1);
    //получаем декриптор очереди от клиента
    int msqid = msgget(key, 0666 | IPC_CREAT);
    // printf("Its in server%d\n", msqid);
    
    while (1) {
        //получаем из очереди любые! сообщений
        msgrcv(msqid, &Message_from, sizeof(Message_from) - sizeof(Message_from.type), 0, 0);
        // printf("Server receiver mes! Its type is %ld\n", Message_from.type);

        if (Message_from.type == 1) {
            ++changing_number;
        }
        if (Message_from.type == 2) {
            key_t key_getnum = ftok(for_key, 2);
            int msqid_getnum = msgget(key_getnum, 0666 | IPC_CREAT);

            Message_to.type = 3;
            char buff[50];
            sprintf(buff, "%d", changing_number);
            strcpy(Message_to.mes, buff);

            msgsnd(msqid_getnum, &Message_to, sizeof(Message_to) - sizeof(Message_to.type), 0);
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    setbuf(stdout, 0);

    int N;
    scanf("%d", &N);

    pid_t client, server;
    client = fork();

    if (client == 0) {
        cclient(argv[0], n);
        exit(0);
    }

    server = fork();

    if (server == 0) {
        usleep(1000);
        sserver(argv[0]);
        exit(0);
    }

    while(wait(NULL) != -1);

    return 0;
}