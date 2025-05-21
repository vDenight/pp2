//
// Created by mrybczynski on 5/21/2025.
//

#ifndef ARRAY_2D_H
#define ARRAY_2D_H

int create_array_2d_2(int ***ptr, int width, int height);
void destroy_array_2d(int ***ptr, int height);
void display_array_2d(int **ptr, int width, int height);
int sum_array_2d(int **ptr, int width, int height);
int sum_row(int *ptr, int width);

enum create_code {
    CREATE_OK = 0,
    CREATE_INPUT_ERROR = 1,
    CREATE_ALLOC_FAIL = 2
};
#endif //ARRAY_2D_H
