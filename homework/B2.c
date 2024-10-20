#include <stdio.h>
int main(void) {
    long long int blyat;
    unsigned long long pizda;
    int nahui = 0;
    scanf("%lld", &blyat);
    pizda = blyat;
    while (pizda != 0) {
        if (pizda % 2 == 1)
            nahui++;
        pizda = pizda / 2;
    }
    printf("%d", nahui);
}