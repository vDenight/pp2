//
// Created by mrybczynski on 4/22/2025.
//

#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }


    a->ptr = malloc(N * sizeof(int));

    if (a->ptr == NULL) {
        return 2;
    }

    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {

    if (cb == NULL || N <= 0) {
        return 1;
    }

    struct circular_buffer_t* circ_buff = malloc(sizeof(struct circular_buffer_t));

    if (circ_buff == NULL) {
        return 2;
    }

    circ_buff->ptr = malloc(N * sizeof(int));
    if (circ_buff->ptr == NULL) {
        free(circ_buff);
        return 2;
    }

    *cb = circ_buff;

    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL) {
        return;
    }
    free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a == NULL) {
        return;
    }
    circular_buffer_destroy(*a);
    free(*a);
}
//
// int circular_buffer_push_back(struct circular_buffer_t *cb, int value);
// int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code);
// int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code);
//
// int circular_buffer_empty(const struct circular_buffer_t *a);
// int circular_buffer_full(const struct circular_buffer_t *a);
//
// void circular_buffer_display(const struct circular_buffer_t *a);
