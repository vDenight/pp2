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
    struct array_t* my_array_add = {0};

    printf("Podaj rozmiar tablicy: ");
    int scanf_val = scanf("%d", &arr_capacity);

    if (scanf_val != 1) {
        printf("Incorrect input");
        return MAIN_INCORRECT_INPUT;
    }

    int create_val = array_create_struct(&my_array_add, arr_capacity);

    if (create_val == ARRAY_CREATE_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return MAIN_ALLOC_FAIL;
    }

    if (create_val == ARRAY_CREATE_INCORRECT_DATA) {
        printf("Incorrect input data");
        return MAIN_INCORRECT_INPUT_DATA;
    }

    struct array_t my_array = *my_array_add;

    int opt_num = 0;
    int act_num = 0;
    int act_val = 0;

    _Bool run = 1;

    while (run) {

        printf("Co chcesz zrobic: ");
        scanf_val = scanf("%d", &opt_num);

        if (scanf_val != 1) {
            printf("Incorrect input");
            array_destroy_struct(&my_array_add);
            return MAIN_INCORRECT_INPUT;
        }

        switch (opt_num) {
            case 0:
                run = 0;
                break;
            case 1:
                printf("Podaj kolejne liczby, które mają zostać dodane do tablicy: ");
                while (1) {
                    scanf_val = scanf("%d", &act_num);
                    if (scanf_val != 1) {
                        printf("Incorrect input");
                        array_destroy_struct(&my_array_add);
                        return MAIN_INCORRECT_INPUT;
                    }
                    if (act_num == 0) break;
                    act_val = array_push_back(&my_array, act_num);
                    if (act_val == ARRAY_PUSH_FAIL) {
                        printf("Buffer is full\n");
                        break;
                    }
                }
                if (my_array.size == 0) {
                    printf("Buffer is empty\n");
                } else {
                    array_display(&my_array);
                }
                break;
            case 2:
                printf("Podaj kolejne liczby, które mają zostać usuniete z tablicy: ");
                while (1) {
                    scanf_val = scanf("%d", &act_num);
                    if (scanf_val != 1) {
                        printf("Incorrect input");
                        array_destroy_struct(&my_array_add);
                        return MAIN_INCORRECT_INPUT;
                    }
                    if (act_num == 0) break;
                    array_remove_item(&my_array, act_num);
                }
                if (my_array.size == 0) {
                    printf("Buffer is empty\n");
                } else {
                    array_display(&my_array);
                }
                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    }

    array_destroy_struct(&my_array_add);
    return MAIN_OK;
}