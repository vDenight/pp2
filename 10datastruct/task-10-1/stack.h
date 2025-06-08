//
// Created by mrybczynski on 6/9/2025.
//

#ifndef STACK_H
#define STACK_H

struct stack_t
{
    int head;
    int capacity;
    int *data;
};

int stack_init(struct stack_t **stack, int N);
int stack_push(struct stack_t *stack, int value);
int stack_pop(struct stack_t *stack, int *err_code);
void stack_display(const struct stack_t *stack);
void stack_free(struct stack_t *stack);

enum stack_code {
    STACK_OK = 0,
    STACK_WRONG_INPUT = 1,
    STACK_ALLOC_FAIL = 2,
    STACK_EMPTY = 2
};

#endif //STACK_H
