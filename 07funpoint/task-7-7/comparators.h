//
// Created by mrybczynski on 5/29/2025.
//

#ifndef COMPARATORS_H
#define COMPARATORS_H

#define COMP_ERROR 2

int comp_min(const int *ptr1, const int *ptr2, int width);
int comp_max(const int *ptr1, const int *ptr2, int width);
int comp_sum(const int *ptr1, const int *ptr2, int width);

int sort_rows(int** tab, int width, int height, int (*comp)(const int*, const int*, int));

#endif //COMPARATORS_H
