#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL)
        return 1;
    int symbol;
    int flag = 0;
    while ((symbol = fgetc(f)) != EOF) {
        if (symbol == '\n') {
            if (flag == 1) {
                flag = 0;
                printf("\n");
            }
            else
                flag = 1;
            continue;
        }
        if (flag)
            printf("%c", symbol);
    }
    fclose(f);
    return 0;
}