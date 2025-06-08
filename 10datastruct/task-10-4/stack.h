//
// Created by mcihal on 08.06.25.
//

#ifndef STACK_H
#define STACK_H

struct stack_t
{
    char *sentence;
    struct stack_t *prev;
};

int stack_push(struct stack_t **stack, char *value);
char *stack_pop(struct stack_t **stack, int *err_code);
void stack_destroy(struct stack_t **stack);
int stack_load(struct stack_t **stack, const char *filename);
int stack_save(const struct stack_t *stack, const char *filename);

enum stack_code {
    STACK_OK = 0,
    STACK_WRONG_INPUT = 1,
    STACK_PUSH_ALLOC_FAIL = 2,
    STACK_CANNOT_OPEN_FILE = 2,
    STACK_LOAD_ALLOC_FAIL = 3
};

#endif //STACK_H
