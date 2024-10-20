#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
enum { MAXLEN = 80 };
void split(char* words[], char* str) {
    int index = 0;
    int i = 0;
    //пропустим все пробелы в начале строки
    while (isspace(*(str + i)))
        i++;
    /*на данный момент указатель *(str + i) указывает
    на первую букву первого слова в строке str*/
    while (*(str + i) != '\0') {
        /*добавляем в массив слов указатель
        на первую букву текущего слова*/
        words[index++] = (str + i);
        i++;
        //если конец строки, то нет смысла дальше продолжать
        if (*(str + i) == '\0')
            break;
        //пропустим все остальные буквы текущего слова
        while (!isspace(*(str + i)) && *(str + i) != '\0')
            i++;
        //если конец строки, то нет смысла дальше продолжать
        if (*(str + i) == '\0')
            break;
        /*пробел, находящийся сразу после текущего слова,
        заменем на '\0'*/
        *(str + i) = '\0';
        i++;
        /*пропускаем остальные пробелы (если они есть) вплоть
        до следующего слова или до конца строки*/
        while (isspace(*(str + i)))
            i++;
    }
    words[index] = NULL;
}
void print3(char *words[]) {
    int i = 0;
    while (words[i] != NULL) {
        if (strlen(words[i]) >= 3)
            printf("%c%c%c\n", *words[i], *(words[i] + 1), *(words[i] + 2));
        i++;
    }
}
int main(void) {
    char *words[MAXLEN];
    char str[MAXLEN + 1];
    fgets(str, MAXLEN + 1, stdin);;
    split(words, str);
    print3(words);
}