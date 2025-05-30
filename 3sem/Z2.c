#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
enum {MAXLEN = 1023, MAXWORD = 32};
int split(char *str, char *delim, char *res[], int length) {
    int i = 0;
    res[i] = strtok(str, delim);
    while(res[i] != NULL) {
        if (i >= length)
            return -1;
        res[++i] = strtok(NULL, delim);
    }
    return i;
}
int run_command(char* command) {
    
    char *argv[MAXWORD + 1];
    int len = split(command, " \t\n", argv, MAXWORD);
    if (len == -1) {
        printf("ERROR: Too many arguments\n");
        return 1;
    }
    int status;
    
    pid_t pid;
    if ((pid = fork()) == 0) {
        execvp(argv[0], &argv[0]);
        exit(127);
    }
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status) + 128;
}
int main(void) {
    //важно отключить буфферизацию
    setbuf(stdin, NULL);
    // int fd = open("input.txt", O_RDONLY);
    // dup2(fd, 0);

    char buffer[MAXLEN + 2];
    int result;
    while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *commands[512];
        int len = split(buffer, ";", commands, 512);
        for (int i = 0; i < len; ++i)
            result = run_command(commands[i]);
    }
    return result;
}