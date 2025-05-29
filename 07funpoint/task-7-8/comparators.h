//
// Created by mrybczynski on 5/29/2025.
//

#ifndef COMPARATORS_H
#define COMPARATORS_H

struct point_t
{
    double x;
    double y;
};

int comp_int(const void *ptr1, const void *ptr2);
int comp_double(const void *ptr1, const void *ptr2);
int comp_point(const void *ptr1, const void *ptr2);

int sort(const void *tab, int tab_size, int elem_size, int (*comp)(const void*, const void*));

#endif //COMPARATORS_H
