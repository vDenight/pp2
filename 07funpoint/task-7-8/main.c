#include <stdio.h>
#include <stdlib.h>

#include "comparators.h"

enum data_type {
    INT = 0,
    DOUBLE = 1,
    POINT = 2
};

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

int main(void) {

    int* i_pointer = {0};
    double* d_pointer = {0};
    struct point_t* p_pointer = {0};

    printf("Enter data type: ");

    int data_type;
    if (scanf("%d", &data_type) != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (data_type < 0 || data_type > 2) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    printf("Enter array size: ");

    int arr_size;
    if (scanf("%d", &arr_size) != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (arr_size < 1) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    switch (data_type) {
        case INT:
            i_pointer = calloc(arr_size, sizeof(int));
            if (!i_pointer) {
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }

            printf("Enter ints: ");

            for (int i = 0; i < arr_size; i++) {
                if (scanf("%d", i_pointer + i) != 1) {
                    free(i_pointer);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
            }

            sort(i_pointer, arr_size, sizeof(int), comp_int);

            for (int i = 0; i < arr_size; i++) {
                printf("%d ", *(i_pointer + i));
            }

            free(i_pointer);
            return OK;
        case DOUBLE:
            d_pointer = calloc(arr_size, sizeof(double));
            if (!d_pointer) {
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }

            printf("Enter doubles: ");

            for (int i = 0; i < arr_size; i++) {
                if (scanf("%lf", d_pointer + i) != 1) {
                    free(d_pointer);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
            }

            sort(d_pointer, arr_size, sizeof(double), comp_double);

            for (int i = 0; i < arr_size; i++) {
                printf("%lf ", *(d_pointer + i));
            }

            free(d_pointer);
            return OK;
        case POINT:
            p_pointer = calloc(arr_size, sizeof(struct point_t));
            if (!p_pointer) {
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }

            printf("Enter points: ");

            for (int i = 0; i < arr_size; i++) {
                if (scanf("%lf %lf\n", &((p_pointer + i)->x), &((p_pointer + i)->y)) != 2) {
                    free(p_pointer);
                    printf("Incorrect input");
                    return INCORRECT_INPUT;
                }
            }

            sort(p_pointer, arr_size, sizeof(struct point_t), comp_point);

            for (int i = 0; i < arr_size; i++) {
                printf("%lf %lf\n", ((p_pointer + i)->x), (p_pointer + i)->y);
            }

            free(p_pointer);
            return OK;
        default: return INCORRECT_INPUT;
    }
}