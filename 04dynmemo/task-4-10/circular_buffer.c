//
// Created by mrybczynski on 4/22/2025.
//

#include "circular_buffer.h"

#include <stdio.h>

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }


    a->ptr = malloc(N * sizeof(int));

    if (a->ptr == NULL) {
        return 2;
    }

    a->capacity = N;
    a->begin = 0;
    a->end = 0;
    a->full = 0;

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
    circ_buff->capacity = N;
    circ_buff->begin = 0;
    circ_buff->end = 0;
    circ_buff->full = 0;

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

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (!circular_buffer_validate(cb)) {
        return 1;
    }

    // this is the new index
    int new_end = (cb->end + 1) % cb->capacity;

    // if the buffer was already full we have to move the begin point
    if (cb->full == 1) {
        cb->begin = (cb->begin + 1) % cb->capacity; // move begin
    }
    // if the buffer will be full after the action
    else if (new_end == cb->begin) {
        cb->full = 1; // if it wasn't full before but is full now we need to flag it as full
    }

    *(cb->ptr + cb->end) = value; // assign to old end
    cb->end = new_end;
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (!circular_buffer_validate(a)) {
        if (err_code != NULL)
            *err_code = 1;
        return 0;
    }

    if (circular_buffer_empty(a)) {
        if (err_code != NULL)
            *err_code = 2;
        return 0;
    }

    int pop_value = *(a->ptr + a->begin);
    a->begin = (a->begin + 1) % a->capacity;

    if (a->full == 1) {
        a->full = 0;
    }

    if (err_code != NULL)
        *err_code = 0;

    return pop_value;

}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if (!circular_buffer_validate(a)) {
        if (err_code != NULL)
            *err_code = 1;
        return 0;
    }

    if (circular_buffer_empty(a)) {
        if (err_code != NULL)
            *err_code = 2;
        return 0;
    }

    int pop_value = *(a->ptr + ((a->end - 1 + a->capacity) % a->capacity));
    a->end = (a->end - 1 + a->capacity) % a->capacity;

    if (a->full == 1) {
        a->full = 0;
    }

    if (err_code != NULL)
        *err_code = 0;

    return pop_value;

}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (!circular_buffer_validate(a)) {
        return -1;
    }
    if (a->end == a->begin && a->full == 0) {
        return 1;
    }
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if (!circular_buffer_validate(a)) {
        return -1;
    }
    if (a->end == a->begin && a->full == 1) {
        return 1;
    }
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if (!circular_buffer_validate(a)) {
        return;
    }

    if (!circular_buffer_empty(a)) {
        for (int i = 0; i <= a->capacity; i++) {
            printf("%d ", *(a->ptr + ((a->begin + i) % a->capacity)));
            if (((a->begin + i + 1) % a->capacity) == a->end) {
                printf("\n");
                break;
            }
        }
    }
}

_Bool circular_buffer_validate(const struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL) {
        return 0;
    }

    if (a->capacity <= 0) {
        return 0;
    }

    if (a->end < 0 || a->end >= a->capacity || a->begin < 0 || a->begin >= a->capacity) {
        return 0;
    }

    return 1;
}
