//
// Created by mrybczynski on 6/3/2025.
//
#include "connect.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void* connect(enum data_type_t type, int N, ...) {
    if (N < 1 || type > 4) return NULL;

    va_list tabs;
    va_start(tabs, N);

    void* result;

    switch (type) {
        case data_type_short:
            result = (void*) connect_short(N, tabs);
            break;
        case data_type_int:
            result = (void*) connect_int(N, tabs);
            break;
        case data_type_float:
            result = (void*) connect_float(N, tabs);
            break;
        case data_type_double:
            result = (void*) connect_double(N, tabs);
            break;
        case data_type_long:
            result = (void*) connect_long(N, tabs);
            break;
        default:
            return NULL;
    }

    va_end(tabs);
    return result;
}

short* connect_short(int N, va_list list) {
    short* result = malloc(1 * sizeof(short));
    if (!result) {
        return NULL;
    }
    *result = -1; // setting the first elem to -1
    int res_len = 0;

    for (int i = 0; i < N; i++) {
        // first take out the elem, calc its len and enlarge our array using realloc
        short* new_tab = va_arg(list, short*);
        int new_arr_len = calculate_arr_len(data_type_short, new_tab);
        short* temp = realloc(result, sizeof(short) * (res_len + new_arr_len + 1)); // keep in mind we need to still have -1 at the end
        if (!temp) {
            free(result);
            return NULL;
        }
        result = temp; // successful realloc
        for (int j = 0; j < new_arr_len; j++) {
            *(result + res_len + j) = *(new_tab + j); // copy the data
        }
        *(result + res_len + new_arr_len) = -1; // set last elem to -1
        res_len += new_arr_len;
    }
    return result;
}

int* connect_int(int N, va_list list) {
    int* result = malloc(1 * sizeof(int));
    if (!result) {
        return NULL;
    }
    *result = -1; // setting the first elem to -1
    int res_len = 0;

    for (int i = 0; i < N; i++) {
        // first take out the elem, calc its len and enlarge our array using realloc
        int* new_tab = va_arg(list, int*);
        int new_arr_len = calculate_arr_len(data_type_int, new_tab);
        int* temp = realloc(result, sizeof(int) * (res_len + new_arr_len + 1)); // keep in mind we need to still have -1 at the end
        if (!temp) {
            free(result);
            return NULL;
        }
        result = temp; // successful realloc
        for (int j = 0; j < new_arr_len; j++) {
            *(result + res_len + j) = *(new_tab + j); // copy the data
        }
        *(result + res_len + new_arr_len) = -1; // set last elem to -1
        res_len += new_arr_len;
    }
    return result;
}

float* connect_float(int N, va_list list) {
    float* result = malloc(1 * sizeof(float));
    if (!result) {
        return NULL;
    }
    *result = -1; // setting the first elem to -1
    int res_len = 0;

    for (int i = 0; i < N; i++) {
        // first take out the elem, calc its len and enlarge our array using realloc
        float* new_tab = va_arg(list, float*);
        int new_arr_len = calculate_arr_len(data_type_float, new_tab);
        float* temp = realloc(result, sizeof(float) * (res_len + new_arr_len + 1)); // keep in mind we need to still have -1 at the end
        if (!temp) {
            free(result);
            return NULL;
        }
        result = temp; // successful realloc
        for (int j = 0; j < new_arr_len; j++) {
            *(result + res_len + j) = *(new_tab + j); // copy the data
        }
        *(result + res_len + new_arr_len) = -1; // set last elem to -1
        res_len += new_arr_len;
    }
    return result;
}

double* connect_double(int N, va_list list) {
    double* result = malloc(1 * sizeof(double));
    if (!result) {
        return NULL;
    }
    *result = -1; // setting the first elem to -1
    int res_len = 0;

    for (int i = 0; i < N; i++) {
        // first take out the elem, calc its len and enlarge our array using realloc
        double* new_tab = va_arg(list, double*);
        int new_arr_len = calculate_arr_len(data_type_double, new_tab);
        double* temp = realloc(result, sizeof(double) * (res_len + new_arr_len + 1)); // keep in mind we need to still have -1 at the end
        if (!temp) {
            free(result);
            return NULL;
        }
        result = temp; // successful realloc
        for (int j = 0; j < new_arr_len; j++) {
            *(result + res_len + j) = *(new_tab + j); // copy the data
        }
        *(result + res_len + new_arr_len) = -1; // set last elem to -1
        res_len += new_arr_len;
    }
    return result;
}

long* connect_long(int N, va_list list) {
    long* result = malloc(1 * sizeof(long));
    if (!result) {
        return NULL;
    }
    *result = -1; // setting the first elem to -1
    int res_len = 0;

    for (int i = 0; i < N; i++) {
        // first take out the elem, calc its len and enlarge our array using realloc
        long* new_tab = va_arg(list, long*);
        int new_arr_len = calculate_arr_len(data_type_long, new_tab);
        long* temp = realloc(result, sizeof(long) * (res_len + new_arr_len + 1)); // keep in mind we need to still have -1 at the end
        if (!temp) {
            free(result);
            return NULL;
        }
        result = temp; // successful realloc
        for (int j = 0; j < new_arr_len; j++) {
            *(result + res_len + j) = *(new_tab + j); // copy the data
        }
        *(result + res_len + new_arr_len) = -1; // set last elem to -1
        res_len += new_arr_len;
    }
    return result;
}

int calculate_arr_len(enum data_type_t type, void* arr) {
    int len = 0;
    switch (type) {
        case data_type_short:
            short* short_arr = (short*) arr;
            while (*short_arr != -1) {
                len++;
                short_arr++;
            }
            break;
        case data_type_int:
            int* int_arr = (int*) arr;
            while (*int_arr != -1) {
                len++;
                int_arr++;
            }
            break;
        case data_type_float:
            float* float_arr = (float*) arr;
            while (*float_arr != -1) {
                len++;
                float_arr++;
            }
            break;
        case data_type_double:
            double* double_arr = (double*) arr;
            while (*double_arr != -1) {
                len++;
                double_arr++;
            }
            break;
        case data_type_long:
            long* long_arr = (long*) arr;
            while (*long_arr != -1) {
                len++;
                long_arr++;
            }
            break;
        default: return 0;
    }
    return len;
}
