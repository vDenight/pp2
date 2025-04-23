#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

enum OPTION {
    END_PROGRAM = 0,
    ADD_ELEMENT,
    DOWNLOAD_LAST,
    DOWNLOAD_FIRST,
    DISPLAY,
    IS_EMPTY,
    IS_FULL
};

int main() {
    printf("Podaj rozmiar bufora: ");
    int size = 0;
    int scanf_val = scanf("%d", &size);

    if (scanf_val != 1) {
        goto incorrect_input;
    }

    if (size <= 0) {
        goto incorrect_input_data;
    }

    struct circular_buffer_t* cb;
    int malloc_val = circular_buffer_create_struct(&cb, size);

    if (malloc_val == 2) {
        goto allocation_failed;
    }

    int option = 0;
    int error_val;
    int return_val;
    int add_val;

    while (1) {

        printf("Co chcesz zrobic? ");

        scanf_val = scanf("%d", &option);
        if (scanf_val != 1) {
            circular_buffer_destroy_struct(&cb);
            goto incorrect_input;
        }

        switch (option) {
            case END_PROGRAM:
                circular_buffer_destroy_struct(&cb);
                return 0;
            case ADD_ELEMENT:

                printf("Podaj liczbe ");
                scanf_val = scanf("%d", &add_val);
                if (scanf_val != 1) {
                    circular_buffer_destroy_struct(&cb);
                    goto incorrect_input;
                }

                circular_buffer_push_back(cb, add_val);
                break;
            case DOWNLOAD_LAST:
                return_val = circular_buffer_pop_back(cb, &error_val);
                if (error_val == 2) {
                    printf("Buffer is empty\n");
                    break;
                }
                printf("%d\n", return_val);
                break;
            case DOWNLOAD_FIRST:
                return_val = circular_buffer_pop_front(cb, &error_val);
                if (error_val == 2) {
                    printf("Buffer is empty\n");
                    break;
                }
                printf("%d\n", return_val);
                break;
            case DISPLAY:
                if (circular_buffer_empty(cb)) {
                    printf("Buffer is empty\n");
                    break;
                }
                circular_buffer_display(cb);
                break;
            case IS_EMPTY:
                printf("%d\n", circular_buffer_empty(cb));
                break;
            case IS_FULL:
                printf("%d\n", circular_buffer_full(cb));
                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    }

incorrect_input:
    printf("incorrect input");
    return 1;

incorrect_input_data:
    printf("Incorrect input data");
    return 2;

allocation_failed:
    printf("Failed to allocate memory");
    return 8;
}
