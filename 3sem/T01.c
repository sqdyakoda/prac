#include <stdio.h>
int main(int argc, char *argv[]) {
    unsigned long prev = 0, last = 0xF;
    last = last << (sizeof(unsigned long) * 8 - 4);
    sscanf(argv[1], "%lu", &prev);
    last = prev ^ last;
    printf("%lx %lx\n", prev, last);
    return 0;
}