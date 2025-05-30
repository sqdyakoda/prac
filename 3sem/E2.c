#include <stdio.h>
#include <stdlib.h>
enum { MAXSIZE = 10000 };
double *max(const double *arr, int size) {
    if (size == 0)
        return NULL;
    double *temp = (double *)arr;
    for (int i = 1; i < size; ++i)
        if (*(arr + i) > *temp)
            temp = (double *)arr + i;
    return (double *)temp;
}
void exchange(double *ptr1, double *ptr2) {
    double temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}
void selection_sort(const double *arr, int size) {
    for (int i = 0; i < size; ++i)
        exchange((double *)arr + i, max(arr + i, size - i));
}
int main(void) {
    double array[MAXSIZE];
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%lf", &array[i]);
    if (N >= 18)
        printf("%.1lf\n", *max(array + 4, 14));
    selection_sort(array, N);
    for (int i = 0; i < N; ++i)
        printf("%.1lf ", array[i]);
}