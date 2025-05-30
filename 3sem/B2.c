#include <stdio.h>
int main(void) {
    long long int num1;
    unsigned long long num2;
    int num3 = 0;
    scanf("%lld", &num1);
    num2 = num1;
    while (num2 != 0) {
        if (num2 % 2 == 1)
            num3++;
        num2 = num2 / 2;
    }
    printf("%d", num3);
}