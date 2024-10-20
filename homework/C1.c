#include <math.h>
int is_simple(int n) {
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0)
        return 0;
    for (int i = 3; i < pow(n, 0.5) + 1; i = i + 2) 
        if (n % i == 0)
            return 0;
    return 1;
}