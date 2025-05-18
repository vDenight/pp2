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
int matrix_read(struct matrix_t *m);
// void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);

struct matrix_t* matrix_create_struct(int width, int height);

void matrix_destroy_struct(struct matrix_t **m);

struct matrix_t* matrix_transpose(const struct matrix_t *m);

int matrix_save_b(const struct matrix_t *m, const char *filename);
int matrix_save_t(const struct matrix_t *m, const char *filename);

enum matrix_create_code {
    CREATE_OK = 0,
    CREATE_WRONG_INPUT = 1,
    CREATE_ALLOC_FAIL = 2
};

enum matrix_read_code {
    READ_OK = 0,
    READ_WRONG_INPUT = 1,
    READ_WRONG_FORMAT = 2
};

enum matrix_save_code {
    SAVE_OK = 0,
    SAVE_WRONG_INPUT = 1,
    SAVE_FILE_OPEN_ERROR = 2,
    SAVE_FAIL = 3
};

#endif //MATRIX_H
