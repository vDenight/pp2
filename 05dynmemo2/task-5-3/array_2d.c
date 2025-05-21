//
// Created by mrybczynski on 5/21/2025.
//

#include <stddef.h>
#include "array_2d.h"

#include <stdio.h>
#include <stdlib.h>

int create_array_2d_2(int ***ptr, int width, int height) {
    if (ptr == NULL || width < 1 || height < 1) {
        return CREATE_INPUT_ERROR;
    }
    *ptr = (int**) malloc(sizeof(int*) * height);
    if (*ptr == NULL) return CREATE_ALLOC_FAIL;

    for (int i = 0; i < height; i++) {
        *(*ptr + i) = (int*) malloc(sizeof(int) * width);
        if (*(*ptr + i) == NULL) {
            for(int j = 0; j < i; j++) {
                free(*(*ptr + j));
            }
            free(*ptr);
            return CREATE_ALLOC_FAIL;
        }
    }
    return CREATE_OK;
}

void destroy_array_2d(int ***ptr, int height) {
    for (int i = 0; i < height; i++) {
        free(*(*ptr + i));
    }
    free(*ptr);
}

void display_array_2d(int **ptr, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}

int sum_array_2d(int **ptr, int width, int height) {
    int sum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sum += *(*(ptr + i) + j);
        }
    }
    return sum;
}

int sum_row(int *ptr, int width) {
    int sum = 0;
    for (int i = 0; i < width; i++) {
        sum += *(ptr + i);
    }
    return sum;
}
