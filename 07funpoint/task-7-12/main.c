#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "easter.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

int main(void) {
    int size = 0;
    printf("Podaj liczbe funkcji do wygenerowania: ");
    if (scanf("%d", &size) != 1 ) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (size < 1) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    void (**funcs)(void) = easter(size, print_chicken, print_egg, print_rabbit);
    if (!funcs) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    for (int i = 0; i < size; i++) {
        (*(funcs + i))();
        printf("\n");
    }

    return OK;
}