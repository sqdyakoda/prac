#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    setbuf(stdin, 0);
    int first_char, current_char;
    first_char  = getchar();
    while ((current_char = getchar()) != EOF) {
        pid_t pid = fork();
        while (pid < 0) {
            wait(NULL);
            pid = fork();
        }
        if (pid == 0) {
            //son
            if (current_char == first_char) {
                putchar(first_char);
                putchar(first_char);
            }
            exit(0);
        }
    }
    while (wait(NULL) != -1);
    putchar('\n');
    return 0;
}