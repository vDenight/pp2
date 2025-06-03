#include <stdio.h>
#include "connect.h"

int main(void) {

    int N = 2;
    short* result = connect(data_type_short, N, (short []){18, -13, -10, -1}, (short []){-7, 1, 20, -2, -1});

    while (*result != -1) {
        printf("%d\n", *result);
        result++;
    }

    return 0;
}