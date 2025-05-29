//
// Created by mrybczynski on 5/29/2025.
//
#include "comparators.h"

#include <stdint.h>
#include <stdio.h>

int comp_int(const void *ptr1, const void *ptr2) {
    int* it_1 = (int*) ptr1;
    int* it_2 = (int*) ptr2;

    return *it_1 - *it_2;
}

int comp_double(const void *ptr1, const void *ptr2) {
    double* db_1 = (double*) ptr1;
    double* db_2 = (double*) ptr2;

    if (*db_1 > *db_2) return 1;
    if (*db_1 < *db_2) return -1;
    return 0;
}

int comp_point(const void *ptr1, const void *ptr2) {
    struct point_t* p_1 = (struct point_t*) ptr1;
    struct point_t* p_2 = (struct point_t*) ptr2;

    if (p_1->x != p_2->x) {
        return comp_double(&(p_1->x), &(p_2->x)); // if we already have it why not use it :))
    }
    return comp_double(&(p_1->y), &(p_2->y));
}

int sort(const void *tab, int tab_size, int elem_size, int (*comp)(const void*, const void*)) {
    if (tab == NULL || tab_size < 1 || elem_size < 1 || comp == NULL) return 1;

    uint8_t* byte_tab = (uint8_t*) tab;
    uint8_t temp_byte;

    for (int i = 0; i < tab_size; i++) {
        for (int j = 0; j < tab_size - 1; j++) {
            if (comp(byte_tab + (j * elem_size), byte_tab + ((j + 1) * elem_size)) > 0) {
                for (int k = 0; k < elem_size; k++) {
                    temp_byte = *(byte_tab + (j * elem_size) + k);
                    *(byte_tab+ (j * elem_size) + k) = *(byte_tab + ((j + 1) * elem_size) + k);
                    *(byte_tab + ((j + 1) * elem_size) + k) = temp_byte;
                }
            }
        }
    }

    return 0;
}
