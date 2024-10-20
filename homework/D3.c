#include <stdio.h>
#include <stdlib.h>
enum { MAXLEN = 3 };
char *concat(const char *s1, const char *s2) {
    char *resultptr = malloc(sizeof(char) * 2 * MAXLEN);
    int i = 0;

    // printf("cycle 1:\n");
    while (*s1 != '\0' && *s1 != '\n') {
        // printf("[%c]\t", *s1);
        *(resultptr + i++) = *s1++;
    }
        
    // printf("\ncycle 2:\n");
    while (*s2 != '\0' && *s2 != '\n') {
        // printf("[%c]\t", *s2);
        *(resultptr + i++) = *s2++;
    }
        
    *(resultptr + i) = '\0';
    return resultptr;
}
int main(void) {
    char str1[MAXLEN + 2], str2[MAXLEN + 1];
    fgets(str1, MAXLEN + 2, stdin);
    fgets(str2, MAXLEN + 1, stdin);
    char *ptr = concat(str1, str2);
    int i = 0;
    while (*(ptr + i) != '\0')
        printf("%c", *(ptr + i++));
    free(ptr);
}