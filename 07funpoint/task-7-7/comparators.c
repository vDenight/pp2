//
// Created by mrybczynski on 5/29/2025.
//

#include "comparators.h"

#include <stddef.h>

int comp_min(const int *ptr1, const int *ptr2, int width) {
    if (ptr1 == NULL || ptr2 == NULL || width < 1) return COMP_ERROR;

    int min1 = *ptr1;
    int min2 = *ptr2;

    for (int i = 1; i < width; i++) { // we start from one coz current min is for i = 0
        if (*(ptr1 + i) < min1) min1 = *(ptr1 + i);
        if (*(ptr2 + i) < min2) min2 = *(ptr2 + i);
    }

    if (min1 > min2) return 1;
    if (min1 < min2) return -1;

    return 0;
}

int comp_max(const int *ptr1, const int *ptr2, int width) {
    if (ptr1 == NULL || ptr2 == NULL || width < 1) return COMP_ERROR;

    int max1 = *ptr1;
    int max2 = *ptr2;

    for (int i = 1; i < width; i++) { // we start from one coz current max is for i = 0
        if (*(ptr1 + i) > max1) max1 = *(ptr1 + i);
        if (*(ptr2 + i) > max2) max2 = *(ptr2 + i);
    }

    if (max1 > max2) return 1;
    if (max1 < max2) return -1;

    return 0;
}

int comp_sum(const int *ptr1, const int *ptr2, int width) {
    if (ptr1 == NULL || ptr2 == NULL || width < 1) return COMP_ERROR;

    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < width; i++) { // 0 this time
        sum1 += *(ptr1 + i);
        sum2 += *(ptr2 + i);
    }

    if (sum1 > sum2) return 1;
    if (sum1 < sum2) return -1;

    return 0; // equal
}

int sort_rows(int** tab, int width, int height, int (*comp)(const int*, const int*, int)) {
    if (tab == NULL || *tab == NULL || width < 1 || height < 1 || comp == NULL) return 1;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height - 1; j++) {
            if (comp(*(tab + j), *(tab + j + 1), width) > 0) {
                int* temp = *(tab + j);
                *(tab + j) = *(tab + j + 1);
                *(tab + j + 1) = temp;
            }
        }
    }

    return 0;
}
