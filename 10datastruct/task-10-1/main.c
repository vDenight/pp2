#include <stdio.h>
#include "stack.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    ALLOC_FAIL = 8
};

enum action_code {
    END_APP = 0,
    PUSH = 1,
    POP = 2,
    DISPLAY = 3
};

int main(void) {

    struct stack_t* s;
    int err = stack_init(&s, 10);
    if (err == STACK_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    _Bool running = 1;
    int action;
    while (running) {
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &action) != 1) {
            stack_free(s);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }

        switch (action) {
            case END_APP: {
                running = 0;
                break;
            }
            case PUSH: {
                printf("Podaj liczbe ");
                int value;
                if (scanf("%d", &value) != 1) {
                    stack_free(s);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
                int push_res = stack_push(s, value);
                if (push_res == STACK_ALLOC_FAIL) {
                    stack_free(s);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                break;
            }
            case POP: {
                int err;
                int popped = stack_pop(s, &err);
                if (err == STACK_EMPTY) {
                    printf("Stack is empty\n");
                } else {
                    printf("%d\n", popped);
                }
                break;
            }
            case DISPLAY: {
                if (s->head == -1) {
                    printf("Stack is empty\n");
                } else {
                    stack_display(s);
                    printf("\n");
                }
                break;
            }
            default: {
                printf("Incorrect input data");
                break;
            }
        }
    }

    return 0;
}