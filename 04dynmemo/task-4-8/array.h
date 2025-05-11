//
// Created by mcihal on 11.05.25.
//

#ifndef ARRAY_H
#define ARRAY_H

struct array_t{
    int *ptr;
    int size;
    int capacity;
};

int array_create(struct array_t *a, int N);
int array_push_back(struct array_t *a, int value);
void array_display(const struct array_t *a);
void array_destroy(struct array_t *a);

int array_create_struct(struct array_t **a, int N);
void array_destroy_struct(struct array_t **a);
int array_remove_item(struct array_t *a, int value);

enum array_codes {
    ARRAY_CREATE_OK = 0,
    ARRAY_CREATE_INCORRECT_DATA = 1,
    ARRAY_CREATE_ALLOC_FAIL = 2,
    ARRAY_PUSH_OK = 0,
    ARRAY_PUSH_INCORRECT_DATA = 1,
    ARRAY_PUSH_FAIL = 2
};

#endif //ARRAY_H
