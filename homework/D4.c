#include <stdio.h>
#include <stdlib.h>
enum { MAXLEN = 10000 };

int main(void) {
    double *arr1 = calloc(MAXLEN, sizeof(double));
    double *arr2 = calloc(MAXLEN, sizeof(double));
    int len1, len2, temp;
    double *ptr1 = NULL, *ptr2 = NULL;
    int flag = 1;
    scanf("%d", &len1);
    for (int i = 0; i < len1; ++i) {
        scanf("%lf", arr1 + i);
        if (flag)
            if (*(arr1 + i) < 0) {
                ptr1 = arr1 + i;
                flag = 0;
            }
    }
    scanf("%d", &len2);
    for (int i = 0; i < len2; ++i) {
        scanf("%lf", arr2 + i);
        if (*(arr2 + i) > 0)
            ptr2 = arr2 + i;
    }
    if ((ptr1 != NULL) && (ptr2 != NULL)) {
        temp = *ptr1;
        *ptr1 = *ptr2;
        *ptr2 = temp;
    }
    for (int i = 0; i < len1; ++i)
        printf("%.1lf ", *(arr1 + i));
    printf("\n");
    for (int i = 0; i < len2; ++i)
        printf("%.1lf ", *(arr2 + i));
    free(arr1);
    free(arr2);
}