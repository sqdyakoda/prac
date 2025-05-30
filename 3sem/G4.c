#include <stdio.h>
#include <string.h>
enum { MAXSIZE = 255 };
int main(int argc, char *argv[]) {
    FILE* f = fopen(argv[1], "r+");
    if (f == NULL)
        return 1;
    FILE* temp = tmpfile();
    if (temp == NULL) {
        fclose(f);
        return 1;
    }
    char line[MAXSIZE + 2];
    while (fgets(line, MAXSIZE + 2, f) != NULL)
        if (strstr(line, argv[2]) != NULL)
            fputs(line, temp);
    fclose(f);
    f = fopen(argv[1], "w");
    fseek(temp, 0, SEEK_SET);
    while (fgets(line, MAXSIZE + 2, temp) != NULL)
        fputs(line, f);
    fclose(temp);
    fclose(f);
    return 0;
}