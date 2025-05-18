//
// Created by mcihal on 18.05.25.
//

#include "matrix_utils.h"

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
                free(*(m->ptr + j));
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
                return READ_WRONG_FORMAT;
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

struct matrix_t* matrix_create_struct(int width, int height) {
    if (width < 1 || height < 1) return NULL;

    struct matrix_t *m = malloc(sizeof(struct matrix_t));
    int create_val = matrix_create(m, width, height);
    if (create_val != CREATE_OK) {
        free(m);
        return NULL;
    }
    return m;
}

void matrix_destroy_struct(struct matrix_t **m) {
    if (m == NULL || *m == NULL) return;
    matrix_destroy(*m);
    free(*m);
    *m = NULL;
}

struct matrix_t* matrix_transpose(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) return NULL;
    struct matrix_t *t = matrix_create_struct(m->height, m->width);
    if (t == NULL) return NULL;
    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++) {
            *(*(t->ptr + j) + i) = *(*(m->ptr + i) + j);
        }
    }
    return t;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1 || filename == NULL) return SAVE_WRONG_INPUT;

    FILE *file = fopen(filename, "wb");
    if (file == NULL) return SAVE_FILE_OPEN_ERROR;
    fwrite(&(m->width), sizeof(int), 1, file);
    fwrite(&(m->height), sizeof(int), 1, file);

    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++) {
            fwrite((*(m->ptr + i) + j), sizeof(int), 1, file);
        }
    }
    fclose(file);
    return SAVE_OK;
}

int matrix_save_t(const struct matrix_t *m, const char *filename) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1 || filename == NULL) return SAVE_WRONG_INPUT;

    FILE *file = fopen(filename, "w");
    if (file == NULL) return SAVE_FILE_OPEN_ERROR;
    fprintf(file, "%d %d\n", m->width, m->height);

    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++) {
            fprintf(file, "%d ", *(*(m->ptr + i) + j));
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return SAVE_OK;
}

struct matrix_t* matrix_copy(const struct matrix_t *copy) {
    if (copy == NULL || copy->ptr == NULL || copy->width < 1 || copy->height < 1) return NULL;
    struct matrix_t *m = matrix_create_struct(copy->width, copy->height);
    if (m == NULL) return NULL;

    for (int i = 0; i < copy->height; i++) {
        for (int j = 0; j < copy->width; j++) {
            *(*(m->ptr + i) + j) = *(*(copy->ptr + i) + j); // coping data
        }
    }

    return m;
}

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m1->ptr == NULL || m1->width < 1 ||  m1->height < 1) return NULL;
    if (m2 == NULL || m2->ptr == NULL || m2->width < 1 || m2->height < 1) return NULL;
    if (m1->width != m2->width || m1->height != m2->height) return NULL;

    struct matrix_t *result = matrix_copy(m1);
    if (result == NULL) return NULL;

    for (int i = 0; i < result->height; i++) {
        for (int j = 0; j < result->width; j++) {
            *(*(result->ptr + i) + j) += *(*(m2->ptr + i) + j);
        }
    }
    return result;
}

struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m1->ptr == NULL || m1->width < 1 ||  m1->height < 1) return NULL;
    if (m2 == NULL || m2->ptr == NULL || m2->width < 1 || m2->height < 1) return NULL;
    if (m1->width != m2->width || m1->height != m2->height) return NULL;

    struct matrix_t *result = matrix_copy(m1);
    if (result == NULL) return NULL;

    for (int i = 0; i < result->height; i++) {
        for (int j = 0; j < result->width; j++) {
            *(*(result->ptr + i) + j) -= *(*(m2->ptr + i) + j);
        }
    }
    return result;
}

struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m1->ptr == NULL || m1->width < 1 ||  m1->height < 1) return NULL;
    if (m2 == NULL || m2->ptr == NULL || m2->width < 1 || m2->height < 1) return NULL;
    if (m1->width != m2->height) return NULL;

    struct matrix_t *result = matrix_create_struct(m2->width, m1->height);
    if (result == NULL) return NULL;

    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m2->width; ++j) {
            int sum = 0;
            for (int k = 0; k < m1->width; ++k) {
                sum += *(*(m1->ptr + i) + k) * *(*(m2->ptr + k) + j); // :OOO
            }
            result->ptr[i][j] = sum;
        }
    }

    return result;
}


