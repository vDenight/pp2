#include <stdio.h>
#include "array.h"

enum main_codes {
    MAIN_OK = 0,
    MAIN_INCORRECT_INPUT = 1,
    MAIN_INCORRECT_INPUT_DATA = 2,
    MAIN_ALLOC_FAIL = 8
};

int main() {

    int arr_capacity = 0;
    struct array_t my_array = {0};

    printf("Podaj rozmiar tablicy: ");
    int scanf_val = scanf("%d", &arr_capacity);

    if (scanf_val != 1) {
        printf("Incorrect input");
        return MAIN_INCORRECT_INPUT;
    }

    int create_val = array_create(&my_array, arr_capacity);

    if (create_val == ARRAY_CREATE_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return MAIN_ALLOC_FAIL;
    }

    if (create_val == ARRAY_CREATE_INCORRECT_DATA) {
        printf("Incorrect input data");
        return MAIN_INCORRECT_INPUT_DATA;
    }

    int scanned_num = 0;
    printf("Podaj liczby do zapisania:\n");

    _Bool buffer_is_empty = 1;
    int push_val = 0;

    while (1) {
        scanf_val = scanf("%d", &scanned_num);
        if (scanf_val != 1) {
            printf("Incorrect input");
            array_destroy(&my_array);
            return MAIN_INCORRECT_INPUT;
        }

        if (scanned_num == 0) break;

        push_val = array_push_back(&my_array, scanned_num);
        if (push_val == ARRAY_PUSH_FAIL) {
            printf("Buffer is full\n");
            break;
        }
        buffer_is_empty = 0;
    }
    if (buffer_is_empty) {
        printf("Buffer is empty");
    } else {
        array_display(&my_array);
    }

    array_destroy(&my_array);
    return MAIN_OK;
}