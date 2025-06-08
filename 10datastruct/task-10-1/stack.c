//
// Created by mrybczynski on 6/9/2025.
//

#include "stack.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int stack_init(struct stack_t **stack, int N) {
    if (stack == NULL || N <= 0) {
        return STACK_WRONG_INPUT;
    }
    struct stack_t *new_stack = calloc(1, sizeof(struct stack_t));
    if (!new_stack) {
        return STACK_ALLOC_FAIL;
    }
    new_stack->data = calloc(N, sizeof(int));
    if (!new_stack->data) {
        free(new_stack);
        return STACK_ALLOC_FAIL;
    }
    new_stack->head = -1;
    new_stack->capacity = N;

    *stack = new_stack;
    return STACK_OK;
}

int expand_stack(struct stack_t *stack);

int stack_push(struct stack_t *stack, int value) {
    if (stack == NULL || stack->data == NULL || stack->head >= stack->capacity ||
        stack->head < -1 || stack->capacity <= 0) {
        return STACK_WRONG_INPUT;
    }

    // check if stack is full
    if (stack->head == stack->capacity - 1) {
        if (expand_stack(stack)) {
            return STACK_ALLOC_FAIL;
        }
    }

    // now we now it is not full
    *(stack->data + stack->head + 1) = value;
    stack->head++;

    return STACK_OK;
}

int expand_stack(struct stack_t *stack) {
    if (stack == NULL || stack->data == NULL || stack->head >= stack->capacity ||
        stack->head < -1 || stack->capacity <= 0) {
        return STACK_WRONG_INPUT;
    }

    int new_capacity = stack->capacity * 2;
    int *new_data = realloc(stack->data, new_capacity * sizeof(int));
    if (!new_data) {
        return STACK_ALLOC_FAIL;
    }

    stack->data = new_data;
    stack->capacity = new_capacity;
    return STACK_OK;
}

int stack_pop(struct stack_t *stack, int *err_code) {
    if (stack == NULL || stack->data == NULL || stack->head >= stack->capacity ||
        stack->head < -1 || stack->capacity <= 0) {
        if (err_code) *err_code = STACK_WRONG_INPUT;
        return -1;
    }

    if (stack->head == -1) {
        if (err_code) *err_code = STACK_EMPTY;
        return -1;
    }

    int val = *(stack->data + stack->head);
    *(stack->data + stack->head) = 0;
    stack->head--;
    if (err_code) *err_code = STACK_OK;
    return val;
}

void stack_display(const struct stack_t *stack) {
    if (stack == NULL || stack->data == NULL || stack->head >= stack->capacity ||
    stack->head < -1 || stack->capacity <= 0) {
        return;
    }

    int current = stack->head;
    while (current >= 0) {
        printf("%d ", *(stack->data + current));
        current--;
    }
}

void stack_free(struct stack_t *stack) {
    if (stack == NULL || stack->data == NULL || stack->head >= stack->capacity ||
    stack->head < -1 || stack->capacity <= 0) {
        return;
    }

    free(stack->data);
    free(stack);
}
