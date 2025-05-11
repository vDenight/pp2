//
// Created by mcihal on 11.05.25.
//

#ifndef ARRAY_SHORT_H
#define ARRAY_SHORT_H

short *create_array_short(int N);
short *concatenate_arrays_short(const short *a1, int size1, const short *a2, int size2, int *err_code);
int sort_short(short* tab, int size);
void display_vector_short(const short* tab, int size);

enum error_codes {
    OK = 0,
    INCORRECT_INPUT = 1,
    ALLOC_FAIL = 2
};

#endif //ARRAY_SHORT_H
