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
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);

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

#endif //MATRIX_H
