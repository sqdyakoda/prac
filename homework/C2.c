#include <stdio.h>
#include <math.h>
int strtoint(const char str[], int *res) {
    int notation, len;
    unsigned long int result;
    if (str[0] != '0')
        return -1;
    switch (str[1]) {
        case 'b':
            notation = 2;
            break;
        case 'o':
            notation = 8;
            break;
        case 'x':
            notation = 16;
            break;
        default:
            return -1;
    }
    len = -1;
    for (int i = 2; str[i] != '\0'; ++i) {
        switch (notation) {
            case 2:
                if ((str[i] != 48) && (str[i] != 49))
                    return -1;
            case 8:
                if ((str[i] < 48) || (str[i] > 55)) 
                    return -1;
            case 16:
                if ((str[i] <= 47) || ((str[i] >= 58) && (str[i] <= 64)) || 
                ((str[i] >= 71) && (str[i] <= 96)) || (str[i] >= 103))
                    return -1;
            default:
                break;
        }
        len++;
    }
    result = 0;
    for (int i = 2; str[i] != '\0'; ++i) {
        if ((str[i] >= 48) && (str[i] <= 57))
            result = result + (str[i] - 48) * pow(notation, len);
        else if ((str[i] >= 65) && (str[i] <= 70))
            result = result + (str[i] - 55) * pow(notation, len);
        else
            result = result + (str[i] - 87) * pow(notation, len);
        if (result > 2147483647)
            return -1;
        len--;
    }
    *res = result;
    return 1;
}