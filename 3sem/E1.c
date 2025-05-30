#include <stdio.h>
#include <stdlib.h>
enum { MAXLEN = 80 };
char* findchar(const char* str, char c) {
    while (*str != '\0') {
        if (*str == c)
            return (char*)str;
        str++;
    }
    return NULL;
}
int main(void) {
    char str[MAXLEN + 1];
    fgets(str, MAXLEN + 1, stdin);
    if (findchar(str, '\n'))
        *findchar(str, '\n') = '\0';
    while (findchar(str, 'Q'))
        *findchar(str, 'Q') = 'R';
    printf("%s", str);
}