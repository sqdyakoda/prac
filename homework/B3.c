#include <stdio.h>
void recursive_output(unsigned int n, int q) {
    if (n > 0) {
        recursive_output(n / q, q);
        printf("%d", n % q);
    }
}
int main(void) {
    unsigned int N;
    int Q;
    scanf("%d %d", &N, &Q);
    if ((Q < 2) || (Q > 10))
        return -1;
    else if (Q == 10)
        printf("%d", N);
    else if (N == 0)
        printf("0");
    else
        recursive_output(N, Q);
    putchar('\n');
    return 0;
}