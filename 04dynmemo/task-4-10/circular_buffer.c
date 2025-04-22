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
    if (cb == NULL || cb->ptr == NULL) {
        return 1;
    }
    // this is the new index
    cb->end = (cb->end + 1) % cb->capacity;

    // if the buffer was already full we have to move the begin point
    if (cb->full == 1) {
        cb->begin = (cb->begin + 1) % cb->capacity; // move begin
    } else if ((cb->end + 1) % cb->capacity == cb->begin) {
        cb->full = 1; // if it wasn't full before but is full now we need to flag it as full
    }

    *(cb->ptr + cb->end) = value;

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->ptr == NULL) {
        *err_code = 1;
        return 0;
    }

    if (a->end == a->begin) {
        *err_code = 2;
        return 0;
    }

    int pop_value = *(a->ptr + a->begin);
    a->begin = (a->begin + 1) % a->capacity;
    *err_code = 0;

    if (a->full == 1) {
        a->full = 0;
    }

    return pop_value;

}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->ptr == NULL) {
        *err_code = 1;
        return 0;
    }

    if (a->end == a->begin) {
        *err_code = 2;
        return 0;
    }

    int pop_value = *(a->ptr + a->end);
    a->end = (a->end - 1) % a->capacity;
    *err_code = 0;

    if (a->full == 1) {
        a->full = 0;
    }

    return pop_value;

}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL) {
        return -1;
    }
    if (a->end == a->begin) {
        return 0;
    }
    return 1;
}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL) {
        return -1;
    }
    if (a->full == 1) {
        return 1;
    }
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL) {
        return;
    }
    int i = 0;
    while (a->begin != a->end) {
        printf("%d ", *(a->ptr + ((a->begin + i) % a->capacity)));
        if (((a->begin + i) % a->capacity) == a->end - 1) {
            printf("\n");
            break;
        }
        i++;
    }
}
