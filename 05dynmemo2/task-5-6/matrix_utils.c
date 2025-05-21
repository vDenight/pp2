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
            *(*(result->ptr + i) + j) = sum;
        }
    }

    return result;
}

struct matrix_t* matrix_load_b(const char *filename, int *err_code) {
    if (filename == NULL) {
        if (err_code != NULL) *err_code = LOAD_WRONG_INPUT;
        return NULL;
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        if (err_code != NULL) *err_code = LOAD_OPEN_FILE_ERROR;
        return NULL;
    }

    int width = 0, height = 0;
    if (fread(&width, sizeof(int), 1, file) != 1 ||
        fread(&height, sizeof(int), 1, file) != 1 ||
        width < 1 || height < 1) {
        if (err_code != NULL) *err_code = LOAD_FILE_CORRUPTED;
        fclose(file);
        return NULL;
    }

    // lets create struct now
    struct matrix_t* m = matrix_create_struct(width, height);
    if (m == NULL) {
        if (err_code != NULL) *err_code = LOAD_ALLOC_FAIL;
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < m->height; i++) {
        int fread_val = (int) fread(*(m->ptr + i), sizeof(int), m->width, file);
        if (fread_val != m->width) {
            if (err_code != NULL) *err_code = LOAD_FILE_CORRUPTED;
            fclose(file);
            matrix_destroy_struct(&m);
            return NULL;
        }
    }

    fclose(file);
    if (err_code) *err_code = 0;
    return m;
}

struct matrix_t* matrix_load_t(const char *filename, int *err_code) {
    if (filename == NULL) {
        if (err_code != NULL) *err_code = LOAD_WRONG_INPUT;
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        if (err_code != NULL) *err_code = LOAD_OPEN_FILE_ERROR;
        return NULL;
    }

    int width = 0, height = 0;
    if (fscanf(file, "%d %d", &width, &height) != 2 ||
        width < 1 || height < 1) {
        if (err_code != NULL) *err_code = LOAD_FILE_CORRUPTED;
        fclose(file);
        return NULL;
        }

    // lets create struct now
    struct matrix_t* m = matrix_create_struct(width, height);
    if (m == NULL) {
        if (err_code != NULL) *err_code = LOAD_ALLOC_FAIL;
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++) {
            if (fscanf(file, "%d", *(m->ptr + i) + j) != 1) {
                if (err_code != NULL) *err_code = LOAD_FILE_CORRUPTED;
                fclose(file);
                matrix_destroy_struct(&m);
                return NULL;
            }
        }
    }

    fclose(file);
    if (err_code) *err_code = 0;
    return m;
}


