#include <stdio.h>
int NOD(int a, int b) {
    while ((a != 0) && (b != 0)) {
        if (b > a) 
            b %= a;
        else 
            a %= b;
    }
    if (a == 0)
        return b;
    return a;
}
int main(void) {
    unsigned int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", NOD(a, b));
}