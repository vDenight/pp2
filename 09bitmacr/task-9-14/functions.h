//
// Created by mcihal on 07.06.25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>

#define CREATE_READ_FUNCTIONS(TYPE, FORMAT) \
    int read_##TYPE(TYPE *data, int size) { \
        if (data == NULL || size < 1) return 1; \
        for (int i = 0; i < size; i++) { \
            if (scanf(FORMAT, data + i) != 1) return 2; \
        } \
        return 0; \
    } \

#define CREATE_DISPLAY_FUNCTIONS(TYPE, FORMAT) \
    void display_##TYPE(const TYPE *data, int size) { \
        if (data == NULL || size < 1) return; \
        for (int i = 0; i < size; i++) { \
            printf(FORMAT " ", *(data + i)); \
        } \
    } \

#define CREATE_SORT_FUNCTIONS(TYPE) \
    int compare_##TYPE(const void* a, const void* b) { \
        if (*(TYPE*)a > *(TYPE*)b) return 1; \
        if (*(TYPE*)a < *(TYPE*)b) return -1; \
        return 0; \
        } \
        \
        int sort_##TYPE(TYPE *data, int size) { \
        if (data == NULL || size < 1) return 1; \
        qsort(data, size, sizeof(TYPE), compare_##TYPE); \
        return 0; \
    } \


#endif //FUNCTIONS_H
