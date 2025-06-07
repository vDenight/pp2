#include <stdio.h>

unsigned long long add(unsigned long long a, unsigned long long b) {
    unsigned long long c = 0ULL;
    unsigned long long i = 1ULL;
    _Bool reminder = 0;
    while (i) {
        if (reminder == 0) {
            if (a & i && b & i) {
                c = c & ~i;
                reminder = 1;
            } else if (!(a & i) && !(b & i)) {
                c = c & ~i;
            } else {
                c = c | i;
            }
        } else {
            if (a & i && b & i) {
                c = c | i;
            } else if (!(a & i) && !(b & i)) {
                c = c | i;
                reminder = 0;
            } else {
                c = c & ~i;
            }
        }

        i = i << 1ULL;
    }
    return c;
}

int main(void) {
    unsigned long long a;
    unsigned long long b;
    unsigned long long c;

    printf("Enter numbers: ");
    if (scanf("%llu %llu", &a, &b) != 2) {
        printf("Incorrect input");
        return 1;
    }

    c = add(a, b);
    printf("%llu", c);

    return 0;
}