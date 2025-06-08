#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    NOT_ENOUGH_DATA = 3,
    ALLOC_FAIL = 8
};

enum sort_action {
    ASC = 0,
    DSC = 1
};

int main(void) {
    struct doubly_linked_list_t* d1 = dll_create();
    if (!d1) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    int input;

    printf("Enter list (-1 when done): ");
    while (1) {
        if (scanf("%d", &input) != 1) {
            dll_clear(d1);
            free(d1);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }
        if (input == -1) break;

        int push_val = dll_push_back(d1, input);
        if (push_val == 2) {
            dll_clear(d1);
            free(d1);
            printf("Failed to allocate memory");
            return ALLOC_FAIL;
        }
    }

    if (dll_size(d1) == 0) {
        dll_clear(d1);
        free(d1);
        printf("Not enough data available");
        return NOT_ENOUGH_DATA;
    }

    int method;
    printf("Choose sorting (0 or 1): ");
    if (scanf("%d", &method) != 1) {
        dll_clear(d1);
        free(d1);
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (method < 0 || method > 1) {
        dll_clear(d1);
        free(d1);
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }
    switch (method) {
        case ASC: {
            dll_sort_asc(d1);
            break;
        }
        case DSC: {
            dll_sort_desc(d1);
            break;
        }
        default: break;
    }
    dll_display(d1); putchar('\n');
    dll_display_reverse(d1); putchar('\n');

    dll_clear(d1);
    free(d1);
    return OK;
}