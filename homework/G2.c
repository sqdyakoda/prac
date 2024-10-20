#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE* f = fopen(argv[1], "r+");
    if (f == NULL)
        return 1;
    char num;
    fread(&num, sizeof(char), 1, f);     
    fseek(f, 0, SEEK_END);
    if (ftell(f) >= 2) {
        fseek(f, 1, SEEK_SET);
        fwrite(&num, sizeof(char), 1, f);
    }
    fclose(f);
    return 0;
}