#include <stdio.h>
#include <math.h>
void add(double *n, int size) {
    FILE* f = fopen("doubles.bin", "w");
    fwrite(n, sizeof(double), size, f);
    fclose(f);
}
int main(int argc, char *argv[]) {
    // double arr[5] = {-11, 5, 12.6, 12.5, -100.8};
    // add(arr, 1);
    
    FILE* f = fopen(argv[1], "r+");
    if (f == NULL)
        return 1;
    fseek(f, 0, SEEK_END);
    long int size = ftell(f);
    if (size < 4) {
        fclose(f);
        return 0;
    }
    fseek(f, 0, SEEK_SET);
    double maxnum, temp, prev;
    fread(&maxnum, sizeof(double), 1, f);
    while (ftell(f) != size) {
        fread(&temp, sizeof(double), 1, f);
        if (temp > maxnum)
            maxnum = temp;
    }
    fseek(f, 0, SEEK_SET);
    while (1) {
        fread(&temp, sizeof(double), 1, f);
        if (fabs(temp - maxnum) < 0.0000000000000000000001)
            break;
    }
    prev = maxnum;
    while (ftell(f) != size) {
        fread(&temp, sizeof(double), 1, f);
        fseek(f, -sizeof(double), SEEK_CUR);
        fwrite(&prev, sizeof(double), 1, f);
        prev = temp;
    }
    fwrite(&prev, sizeof(double), 1, f);
    printf("max = %.1f\n", maxnum);
    fclose(f);
    return 0;
}