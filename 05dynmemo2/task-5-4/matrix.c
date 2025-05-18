//
// Created by mcihal on 18.05.25.
//

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int matrix_create(struct matrix_t *m, int width, int height) {

    if (m == NULL || width < 1 || height < 1) {
        return CREATE_WRONG_INPUT;
    }

    m->width = width;
    m->height = height;

    m->ptr = malloc(height * sizeof(int*));
    if (m->ptr == NULL) {
        return CREATE_ALLOC_FAIL;
    }

    for (int i = 0; i < height; i++) {
        *(m->ptr + i) = malloc(width * sizeof(int));
        if (*(m->ptr + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(m->ptr + i));
            }
            free(m->ptr);
            return CREATE_ALLOC_FAIL;
        }
    }

    return CREATE_OK;
}

int matrix_read(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) {
        return READ_WRONG_INPUT;
    }

    int scanf_val = 0;
    int scanned = 0;
    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++) {
            scanf_val = scanf("%d", &scanned);
            if (scanf_val != 1) {
                return READ_WRONG_INPUT;
            }
            *(*(m->ptr + i) + j) = scanned;
        }
    }
    return READ_OK;
}

void matrix_display(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) {
        return;
    }

    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++) {
            printf("%d ", *(*(m->ptr + i) + j));
        }
        printf("\n");
    }
}

void matrix_destroy(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) {
        return;
    }
    for (int i = 0; i < m->height; i++) {
        free(*(m->ptr + i));
    }
    free(m->ptr);
}
