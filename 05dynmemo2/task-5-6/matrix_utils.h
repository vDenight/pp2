//
// Created by mcihal on 18.05.25.
//

#ifndef MATRIX_H
#define MATRIX_H

struct matrix_t{
    int **ptr;
    int width;
    int height;
};

int matrix_create(struct matrix_t *m, int width, int height);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);

struct matrix_t* matrix_create_struct(int width, int height);
void matrix_destroy_struct(struct matrix_t **m);

struct matrix_t* matrix_copy(const struct matrix_t *copy);

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2);

struct matrix_t* matrix_load_b(const char *filename, int *err_code);
struct matrix_t* matrix_load_t(const char *filename, int *err_code);

enum matrix_create_code {
    CREATE_OK = 0,
    CREATE_WRONG_INPUT = 1,
    CREATE_ALLOC_FAIL = 2
};

enum matrix_load_code {
    LOAD_OK = 0,
    LOAD_WRONG_INPUT = 1,
    LOAD_OPEN_FILE_ERROR = 2,
    LOAD_FILE_CORRUPTED = 3,
    LOAD_ALLOC_FAIL = 4
};

#endif //MATRIX_H
