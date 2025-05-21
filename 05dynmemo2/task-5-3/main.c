#include <stdio.h>

#include "array_2d.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

int main(void) {
    int width = 0, height = 0;
    int** tab;
    int code;

    printf("Podaj szerokosc i wysokosc: ");
    code = scanf("%d %d", &width, &height);

    if (code != 2) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (width < 1 || height < 1) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    code = create_array_2d_2(&tab, width, height);

    if (code == CREATE_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            code = scanf("%d", (*(tab + i) + j));
            if (code != 1) {
                printf("Incorrect input");
                destroy_array_2d(&tab, height);
                return INCORRECT_INPUT;
            }
        }
    }

    display_array_2d(tab, width, height);
    for (int i = 0; i < height; i++) {
        printf("%d\n", sum_row(*(tab + i), width));
    }
    printf("%d\n", sum_array_2d(tab, width, height));

    destroy_array_2d(&tab, height);

    return 0;
}