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

enum link_method {
    ZIP = 0,
    BEGINNING = 1,
    END = 2
};

int main(void) {
    struct doubly_linked_list_t* d1 = dll_create();
    struct doubly_linked_list_t* d2 = dll_create();
    if (!d1 || !d2) {
        if (d1) free(d1);
        if (d2) free(d2);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    int input;

    printf("Enter first list (-1 when done): ");
    while (1) {
        if (scanf("%d", &input) != 1) {
            dll_clear(d1);
            dll_clear(d2);
            free(d1);
            free(d2);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }
        if (input == -1) break;

        int push_val = dll_push_back(d1, input);
        if (push_val == 2) {
            dll_clear(d1);
            dll_clear(d2);
            free(d1);
            free(d2);
            printf("Failed to allocate memory");
            return ALLOC_FAIL;
        }
    }

    printf("Enter second list (-1 when done): ");
    while (1) {
        if (scanf("%d", &input) != 1) {
            dll_clear(d1);
            dll_clear(d2);
            free(d1);
            free(d2);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }
        if (input == -1) break;

        int push_val = dll_push_back(d2, input);
        if (push_val == 2) {
            dll_clear(d1);
            dll_clear(d2);
            free(d1);
            free(d2);
            printf("Failed to allocate memory");
            return ALLOC_FAIL;
        }
    }

    if (dll_size(d1) == 0 && dll_size(d2) == 0) {
        dll_clear(d1);
        dll_clear(d2);
        free(d1);
        free(d2);
        printf("Not enough data available");
        return NOT_ENOUGH_DATA;
    }

    int method;
    printf("Choose method (0, 1 or 2): ");
    if (scanf("%d", &method) != 1) {
        dll_clear(d1);
        dll_clear(d2);
        free(d1);
        free(d2);
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (method < 0 || method > 2) {
        dll_clear(d1);
        dll_clear(d2);
        free(d1);
        free(d2);
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }
    switch (method) {
        case ZIP: {
            dll_concat_zip(d1, d2);
            break;
        }
        case BEGINNING: {
            dll_concat_begin(d1, d2);
            break;
        }
        case END: {
            dll_concat_end(d1, d2);
            break;
        }
        default: break;
    }
    dll_display(d1); putchar('\n');
    dll_display_reverse(d1); putchar('\n');

    dll_clear(d1);
    dll_clear(d2);
    free(d1);
    free(d2);
    return OK;
}