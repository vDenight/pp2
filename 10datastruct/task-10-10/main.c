#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    ALLOC_FAIL = 8
};

enum action_code {
    END_PROGRAM = 0,
    PUSH_BACK = 1,
    POP_BACK = 2,
    PUSH_FRONT = 3,
    POP_FRONT = 4,
    PUSH_INDEX = 5,
    POP_INDEX = 6,
    SHOW_BACK = 7,
    SHOW_FRONT = 8,
    CHECK_EMPTY = 9,
    SHOW_SIZE = 10,
    CLEAR_LIST = 11,
    SHOW_INDEX = 12,
    SHOW_LIST = 13,
    SHOW_LIST_REVERSE = 14
};

int main(void) {

    struct doubly_linked_list_t* dll = dll_create();

    _Bool running = 1;
    int action;

    while (running) {
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &action) != 1) {
            dll_clear(dll);
            free(dll);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }
        switch (action) {
            case END_PROGRAM: {
                running = 0;
                break;
            }
            case PUSH_BACK: {
                int elem;
                printf("Podaj liczbe ");
                if (scanf("%d", &elem) != 1) {
                    dll_clear(dll);
                    free(dll);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
                int push_val = dll_push_back(dll, elem);
                if (push_val == 2) {
                    dll_clear(dll);
                    free(dll);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                break;
            }
            case PUSH_FRONT: {
                int elem;
                printf("Podaj liczbe ");
                if (scanf("%d", &elem) != 1) {
                    dll_clear(dll);
                    free(dll);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
                int push_val = dll_push_front(dll, elem);
                if (push_val == 2) {
                    dll_clear(dll);
                    free(dll);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                break;
            }
            case PUSH_INDEX: {
                int elem;
                int index;
                printf("Podaj liczbe ");
                if (scanf("%d", &elem) != 1) {
                    dll_clear(dll);
                    free(dll);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
                printf("Podaj index ");
                if (scanf("%d", &index) != 1) {
                    dll_clear(dll);
                    free(dll);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
                int push_val = dll_insert(dll, index, elem);
                if (push_val == 1) {
                    printf("Index out of range\n");
                }
                if (push_val == 2) {
                    dll_clear(dll);
                    free(dll);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                break;
            }
            case POP_BACK: {
                int err;
                int pop_val = dll_pop_back(dll, &err);
                if (err == 1) {
                    printf("List is empty\n");
                } else {
                    printf("%d\n", pop_val);
                }
                break;
            }
            case POP_FRONT: {
                int err;
                int pop_val = dll_pop_front(dll, &err);
                if (err == 1) {
                    printf("List is empty\n");
                } else {
                    printf("%d\n", pop_val);
                }
                break;
            }
            case POP_INDEX: {
                if (dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }
                int index;
                printf("Podaj index ");
                if (scanf("%d", &index) != 1) {
                    dll_clear(dll);
                    free(dll);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
                int err;
                int pop_val = dll_remove(dll, index, &err);
                if (err == 1) {
                    printf("Index out of range\n");
                } else {
                    printf("%d\n", pop_val);
                }
                break;
            }
            case SHOW_BACK: {
                if (dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }
                printf("%d", dll_back(dll, NULL));
                break;
            }
            case SHOW_FRONT: {
                if (dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }
                printf("%d", dll_front(dll, NULL));
                break;
            }
            case SHOW_INDEX: {
                if (dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }
                int index;
                printf("Podaj index ");
                if (scanf("%d", &index) != 1) {
                    dll_clear(dll);
                    free(dll);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
                int err;
                int show_val = dll_at(dll, index, &err);
                if (err == 1) {
                    printf("Index out of range\n");
                } else {
                    printf("%d\n", show_val);
                }
                break;
            }
            case CHECK_EMPTY: {
                printf("%d\n", dll_is_empty(dll));
                break;
            }
            case SHOW_SIZE: {
                printf("%d\n", dll_size(dll));
                break;
            }
            case CLEAR_LIST: {
                dll_clear(dll);
                break;
            }
            case SHOW_LIST: {
                dll_display(dll);
                break;
            }
            case SHOW_LIST_REVERSE: {
                dll_display_reverse(dll);
                break;
            }
            default: {
                printf("Incorrect input data\n");
                break;
            }
        }
    }

    dll_clear(dll);
    free(dll);
    return OK;
}