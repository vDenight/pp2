//
// Created by mrybczynski on 4/23/2025.
//

#include "vector.h"

#include <stdio.h>

int vector_create_struct(struct vector_t **a, int N) {

    if (a == NULL || N <= 0) {
        return 1;
    }

    struct vector_t *v = NULL;
    v = (struct vector_t *)malloc(sizeof(struct vector_t));

    if (v == NULL) {
        return 2;
    }

    int create_val = vector_create(v, N);

    if (create_val != 0) {
        free(v);
        return 2;
    }

    v->capacity = N;
    v->size = 0;

    *a = v;
    return 0;
}

void vector_destroy_struct(struct vector_t **a) {
    if (a == NULL)
        return;
    if (*a == NULL)
        return;

    vector_destroy(*a);
    free(*a);
}

int vector_create(struct vector_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }

    a->ptr = (int *)malloc(sizeof(int) * N);
    if (a->ptr == NULL) {
        return 2;
    }

    a->capacity = N;
    a->size = 0;
    return 0;
}

void vector_destroy(struct vector_t *a) {
    if (a == NULL)
        return;
    if (a->ptr == NULL)
        return;

    free(a->ptr);
}

void vector_display(const struct vector_t *a) {
    // some validation
    if (a == NULL)
        return;;

    if (a->size <= 0 || a->size > a->capacity ||
        a->capacity <= 0 || a->ptr == NULL)
        return;


    for (int i = 0; i < a->size; i++) {
        printf("%d ", a->ptr[i]);
    }
    printf("\n");
}

int vector_push_back(struct vector_t *a, int value) {
    // some validation
    if (a == NULL)
        return 1;

    if (a->size < 0 || a->size > a->capacity ||
        a->capacity <= 0 || a->ptr == NULL)
        return 1;


    if (a->size == a->capacity) {
        int old_capacity = a->capacity;

        a->capacity *= 2;

        int* new_ptr = realloc(a->ptr, sizeof(int) * a->capacity);
        if (new_ptr == NULL) {
            a->capacity = old_capacity;
            return 2;
        }
        a->ptr = new_ptr;
    }

    (*(a->ptr + a->size)) = value;
    a->size++;
    return 0;
}

int vector_erase(struct vector_t *a, int value) {
    // some validation
    if (a == NULL)
        return -1;

    if (a->size < 0 || a->size > a->capacity ||
        a->capacity <= 0 || a->ptr == NULL)
        return -1;

    int new_size = 0;
    int count = 0;
    int* take_point = a->ptr;
    int* add_point = a->ptr;

    while (take_point < a->ptr + a->size) {
        if (*take_point != value) {
            new_size++;
            *add_point = *take_point;
            add_point++;
        } else {
            count++;
        }
        take_point++;
    }

    a->size = new_size;

    if (a->size * 4 < a->capacity) {
        a->capacity /= 2;

        if (a->capacity == 0)
            a->capacity = 1;

        int* new_pointer = (int *)realloc(a->ptr, sizeof(int) * a->capacity);
        if (new_pointer == NULL) {
            return count;
        }
        a->ptr = new_pointer;
    }

    return count;
}
