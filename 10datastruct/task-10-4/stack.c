//
// Created by mcihal on 08.06.25.
//
#include "stack.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int stack_push(struct stack_t **stack, char *value) {
    if (stack == NULL || value == NULL) return STACK_WRONG_INPUT;

    struct stack_t *new_stack_elem = malloc(sizeof(struct stack_t));
    if (!new_stack_elem) {
        return STACK_PUSH_ALLOC_FAIL;
    }

    new_stack_elem->sentence = value;
    new_stack_elem->prev = *stack;
    *stack = new_stack_elem;

    return STACK_OK;
}

char *stack_pop(struct stack_t **stack, int *err_code) {
    if (stack == NULL || *stack == NULL) { if (err_code) *err_code = STACK_WRONG_INPUT; return NULL; }
    char* top_sentence = (*stack)->sentence;
    struct stack_t *stack_new_top = (*stack)->prev;
    free(*stack);
    *stack = stack_new_top;

    if (err_code) *err_code = STACK_OK;
    return top_sentence;
}

void stack_destroy(struct stack_t **stack) {
    if (stack == NULL) return;
    // while (*stack) { // this is a good approach but we need to utilize stack pop so the clang will be happy
    //     struct stack_t *tmp = *stack;
    //     *stack = (*stack)->prev;
    //     free(tmp->sentence);
    //     free(tmp);
    // }
    int err_code = 0;
    while (!err_code) {
        char* top_sentence = stack_pop(stack, &err_code); // pop em all
        free(top_sentence);
    }
}

enum read_sentence_err {
    READ_SENTENCE_OK = 0,
    READ_SENTENCE_DONE = 1,
    READ_SENTENCE_ALLOC_FAIL = 2
};

char* read_sentence(FILE *f, int *err);

int stack_load(struct stack_t **stack, const char *filename) {
    if (stack == NULL || *stack != NULL || filename == NULL) return STACK_WRONG_INPUT;

    FILE* file = fopen(filename, "r");
    if (!file) return STACK_CANNOT_OPEN_FILE;

    char* new_sentence = NULL;
    int read_sentence_err = 0;
    while ((new_sentence = read_sentence(file, &read_sentence_err))) {
        if (stack_push(stack, new_sentence) == STACK_PUSH_ALLOC_FAIL) {
            free(new_sentence);
            fclose(file);
            stack_destroy(stack);
            return STACK_LOAD_ALLOC_FAIL;
        }
    }
    if (read_sentence_err == READ_SENTENCE_ALLOC_FAIL) {
        fclose(file);
        stack_destroy(stack);
        return STACK_LOAD_ALLOC_FAIL;
    }

    fclose(file);
    return STACK_OK;
}

char* read_sentence(FILE *f, int *err) {
    size_t len = 0;
    long current_cursor_pos = ftell(f);

    // first check the sentence length
    int c;
    while (1) {
        c = fgetc(f); // get letter
        len++;
        if (c == '.') { *err = READ_SENTENCE_OK; break; }
        if (c == EOF) { *err = READ_SENTENCE_DONE; return NULL; }
    }

    char* new_sentence = calloc(len + 1, sizeof(char));
    if (!new_sentence) { *err = READ_SENTENCE_ALLOC_FAIL; return NULL; }

    fseek(f, current_cursor_pos, SEEK_SET); // go back to the start

    for (size_t i = 0; i < len; i++) {
        c = fgetc(f);
        *(new_sentence + i) = (char) c;
    }

    return new_sentence;
}

int stack_save(const struct stack_t *stack, const char *filename) {
    if (stack == NULL || filename == NULL) return STACK_WRONG_INPUT;

    FILE *file = fopen(filename, "w");
    if (!file) {
        return STACK_CANNOT_OPEN_FILE;
    }

    struct stack_t* current = (struct stack_t*) stack;
    while (current) {
        fprintf(file, "%s", current->sentence);
        current = current->prev;
    }

    fclose(file);
    return STACK_OK;
}
