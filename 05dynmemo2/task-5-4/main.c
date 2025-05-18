#include <stdio.h>
#include "matrix.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

int main(void) {
    struct matrix_t my_matrix = {0};

    printf("Podaj szerokość i wysokość: ");

    int scanf_val = 0, height = 0, width = 0;
    scanf_val = scanf("%d %d", &width, &height);

    if (scanf_val != 2) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    int create_val = matrix_create(&my_matrix, width, height);

    if (create_val == CREATE_WRONG_INPUT) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }
    if (create_val == CREATE_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Podaj wartości: ");
    int read_val = matrix_read(&my_matrix);
    if (read_val == READ_WRONG_FORMAT) {
        printf("Incorrect input");
        matrix_destroy(&my_matrix);
        return INCORRECT_INPUT;
    }
    matrix_display(&my_matrix);
    matrix_destroy(&my_matrix);

    return OK;
}