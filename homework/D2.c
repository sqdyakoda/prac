#include <stdio.h>
enum { MAXLEN1 = 80, MAXLEN2 = 20 };
int strfind(const char *str, const char *symbols) {
    int result, i;
    result = i = 0;
    while (*(str + result) != '\0' && *(str + result) != '\n' && result < MAXLEN1) {
        while (*(symbols + i) != '\0' && *(symbols + i) != '\n') {
            if (*(str + result) == *(symbols + i))
                return result;
            i++;
        }
        result++;
        i = 0;
    }
    return -1;
}
int main(void) {
    char str1[MAXLEN1 + 2], str2[MAXLEN2 + 1];
    fgets(str1, MAXLEN1 + 2, stdin);
    fgets(str2, MAXLEN2 + 1, stdin);
    printf("%d\n", strfind(str1, str2));
}