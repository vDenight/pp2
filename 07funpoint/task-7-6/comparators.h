//
// Created by mrybczynski on 5/28/2025.
//

#ifndef COMPARATORS_H
#define COMPARATORS_H

int comp_int(int a, int b);
int comp_int_abs(int a, int b);
int comp_int_length(int a, int b);
int comp_int_digit_sum(int a, int b);

int sort_int(int* tab, int size, int (*comparator)(int, int));

#endif //COMPARATORS_H
