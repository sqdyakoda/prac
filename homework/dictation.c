#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
enum { maxlen = 255 };
typedef struct Word {
    char english[maxlen + 2];
    char russian[maxlen + 2];
} Word;
char *removespace(char *str) {
    while (isspace(*str))
        str++;
    char *result = str;
    while (*str != '\0')
        str++;
    str--;
    while (isspace(*str)) {
        str--;
    }
    str++;
    *str = '\0';
    return result;
}
void append(const char *str, Word *word) {
    char *eng = (char*) str;
    char *rus = (char*) str;
    while (*rus != '-')
        rus++;
    *rus = '\0';
    rus++;
    strcpy(word->english, removespace(eng));
    strcpy(word->russian, removespace(rus));
}
int main(int argc, char *argv[]) {
    char line[maxlen + 2];
    FILE *f;
    if (argv[1] == NULL) {
        printf("please enter the input file name: ");
        if (fgets(line, maxlen + 2, stdin) == NULL) {
            printf("error1\n");
            return 0;
        }
        f = fopen(removespace(line), "r");
    } else
        f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("error2\n");
        return 0;
    }
    int capacity = 2;
    Word **array = malloc(sizeof(Word*) * capacity);
    int size = 0;
    while (fgets(line, maxlen + 2, f) != NULL) {
        if (size >= capacity)
            array = realloc(array, (capacity = capacity * 2));
        Word *ptr = (Word*) malloc(sizeof(Word));
        append(line, ptr);
        array[size++] = ptr;
    }
    srand(time(NULL));
    for (int i = size - 1; i >= 0; --i) {
        int j = rand() % (i + 1);
        Word *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    for (int i = 0; i < size; ++i) {
        printf("%s - ", array[i]->russian);
        if (fgets(line, maxlen, stdin) == NULL)
            break;
        removespace(line);
        if (strcmp(line, array[i]->english) == 0)
            printf("CORRECT!\n");
        else
            printf("INCORRECT! Correct answer is '%s'\n", array[i]->english);
    }
    for (int i = 0; i < size; ++i)
        free(array[i]);
    free(array);
    fclose(f);
    return 0;
}