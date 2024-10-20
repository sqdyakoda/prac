#include <stdio.h>
const int MAX_LEN = 100;
int main(void) {
    int len;
    int array[MAX_LEN];
    scanf("%d", &len);
    if ((len < 0) || (len >= 100))
        return -1;
    for (int i = 0; i < len; i++) {
        scanf("%d", &array[i]);
        if (array[i] % 2 == 0)
            printf("%d ", array[i]);
    }
    for (int i = len - 1; i >= 0; i--)
        if (array[i] % 2 != 0)
            printf("%d ", array[i]);
    putchar('\n');
    return 0;
}