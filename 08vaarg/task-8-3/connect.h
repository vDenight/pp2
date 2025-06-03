//
// Created by mrybczynski on 6/3/2025.
//

#ifndef CONNECT_H
#define CONNECT_H

#include <stdarg.h>

#include "data_type.h"

void* connect(enum data_type_t type, int N, ...);

int calculate_arr_len(enum data_type_t type, void* arr);

short* connect_short(int N, va_list list);
int* connect_int(int N, va_list list);
float* connect_float(int N, va_list list);
double* connect_double(int N, va_list list);
long* connect_long(int N, va_list list);


#endif //CONNECT_H
