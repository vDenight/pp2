//
// Created by mcihal on 11.05.25.
//
#include "array.h"

#include <stdio.h>
#include <stdlib.h>

int array_create(struct array_t *a, int N) {

    if (a == NULL || N <= 0) return ARRAY_CREATE_INCORRECT_DATA;
    a->ptr = malloc(sizeof(int) * N);

    if (a->ptr == NULL) return ARRAY_CREATE_ALLOC_FAIL;

    a->size = 0;
    a->capacity = N;

    return ARRAY_CREATE_OK;
}

int array_push_back(struct array_t *a, int value) {
    if (a == NULL) return ARRAY_PUSH_INCORRECT_DATA;
    if (a->ptr == NULL || a->capacity <= 0 || a->size < 0 || a->size > a->capacity) return ARRAY_PUSH_INCORRECT_DATA;
    if (a->size == a->capacity) return ARRAY_PUSH_FAIL;

    *(a->ptr + a->size) = value;
    a->size++;
    return ARRAY_PUSH_OK;
}

void array_display(const struct array_t *a) {
    if (a == NULL) return;
    if (a->ptr == NULL || a->capacity <= 0 || a->size <= 0 || a->size > a->capacity) return;

    for (int i = 0; i < a->size; i++) {
        printf("%d ", *(a->ptr + i));
    }
    printf("\n");
}

void array_destroy(struct array_t *a) {
    if (a == NULL) return;
    if (a->ptr == NULL || a->capacity <= 0 || a->size < 0 || a->size > a->capacity) return;
    free(a->ptr);
    a->ptr = NULL;
}
