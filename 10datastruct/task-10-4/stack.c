//
// Created by mcihal on 08.06.25.
//
#include "stack.h"

int stack_push(struct stack_t **stack, char *value) {

    return STACK_OK;
}

char *stack_pop(struct stack_t **stack, int *err_code);
void stack_destroy(struct stack_t **stack);
int stack_load(struct stack_t **stack, const char *filename);
int stack_save(const struct stack_t *stack, const char *filename);
