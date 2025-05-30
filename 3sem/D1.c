#include <stdio.h>
enum {MAXLEN = 80};
int my_strlen(const char* str) {
    int result = 0;
    while (*(str + result) != '\0' && *(str + result) != '\n')
        result++;
    return result;
}
int main(void) {
    char str[MAXLEN + 1];
    if (fgets(str, MAXLEN + 1, stdin) == NULL)
        printf("EMPTY INPUT");
    else
        printf("%d", my_strlen(str));
}