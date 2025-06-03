#include <stdio.h>
#include <stdlib.h>

#include "connect.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

void* connect_wrapper(enum data_type_t type, int num_arrays, void** arrays_of_pointers_to_arrays);
void destroy_arr_of_arrs(void** arr_of_arr, int N);
void print_result(enum data_type_t type, void* result);

int main(void) {

    int type;
    int N;

    printf("Podaj typ danych do wprowadzenia: ");
    if (scanf("%d", &type) != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (type < 0 || type > 4) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    printf("Podaj liczbe tablic do wprowadzenia: ");
    if (scanf("%d", &N) != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (N < 0) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    // now we need to alloc space for N pointers
    void** arr_of_arr = calloc(N, sizeof(void*));
    if (!arr_of_arr) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }


    // pobieranie tablic
    int elem_num = 0;
    for (int i = 0; i < N; i++) {
        printf("Podaj liczbe elementow: ");
        if (scanf("%d", &elem_num) != 1) {
            destroy_arr_of_arrs(arr_of_arr, N);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }
        if (elem_num < 1) {
            destroy_arr_of_arrs(arr_of_arr, N);
            printf("Incorrect input data");
            return INCORRECT_INPUT_DATA;
        }

        printf("Podaj liczby: ");

        switch (type) {
            case data_type_short: {
                short* arr = malloc((elem_num + 1) * sizeof(short));
                if (!arr) {
                    destroy_arr_of_arrs(arr_of_arr, N);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                // set last elem to -1
                *(arr + elem_num) = -1;
                for (int j = 0; j < elem_num; j++) {
                    if (scanf("%hd", (arr + j)) != 1) {
                        free(arr);
                        destroy_arr_of_arrs(arr_of_arr, N);
                        printf("Failed to allocate memory");
                        return ALLOC_FAIL;
                    }
                }
                *(arr_of_arr + i) = (void*) arr;
                break;
            }
            case data_type_int: {
                int* arr = malloc((elem_num + 1) * sizeof(int));
                if (!arr) {
                    destroy_arr_of_arrs(arr_of_arr, N);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                // set last elem to -1
                *(arr + elem_num) = -1;
                for (int j = 0; j < elem_num; j++) {
                    if (scanf("%d", (arr + j)) != 1) {
                        free(arr);
                        destroy_arr_of_arrs(arr_of_arr, N);
                        printf("Failed to allocate memory");
                        return ALLOC_FAIL;
                    }
                }
                *(arr_of_arr + i) = (void*) arr;
                break;
            }
            case data_type_float: {
                float* arr = malloc((elem_num + 1) * sizeof(float));
                if (!arr) {
                    destroy_arr_of_arrs(arr_of_arr, N);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                // set last elem to -1
                *(arr + elem_num) = -1;
                for (int j = 0; j < elem_num; j++) {
                    if (scanf("%f", (arr + j)) != 1) {
                        free(arr);
                        destroy_arr_of_arrs(arr_of_arr, N);
                        printf("Failed to allocate memory");
                        return ALLOC_FAIL;
                    }
                }
                *(arr_of_arr + i) = (void*) arr;
                break;
            }
            case data_type_double: {
                double* arr = malloc((elem_num + 1) * sizeof(double));
                if (!arr) {
                    destroy_arr_of_arrs(arr_of_arr, N);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                // set last elem to -1
                *(arr + elem_num) = -1;
                for (int j = 0; j < elem_num; j++) {
                    if (scanf("%lf", (arr + j)) != 1) {
                        free(arr);
                        destroy_arr_of_arrs(arr_of_arr, N);
                        printf("Failed to allocate memory");
                        return ALLOC_FAIL;
                    }
                }
                *(arr_of_arr + i) = (void*) arr;
                break;
            }
            case data_type_long: {
                long* arr = malloc((elem_num + 1) * sizeof(long));
                if (!arr) {
                    destroy_arr_of_arrs(arr_of_arr, N);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;
                }
                // set last elem to -1
                *(arr + elem_num) = -1;
                for (int j = 0; j < elem_num; j++) {
                    if (scanf("%hd", (arr + j)) != 1) {
                        free(arr);
                        destroy_arr_of_arrs(arr_of_arr, N);
                        printf("Failed to allocate memory");
                        return ALLOC_FAIL;
                    }
                }
                *(arr_of_arr + i) = (void*) arr;
                break;
            }
            default: break;
        }
    }

    void* result = connect_wrapper(type, N, arr_of_arr);
    if (!result) {
        destroy_arr_of_arrs(arr_of_arr, N);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    print_result(type, result);

    free(result);
    destroy_arr_of_arrs(arr_of_arr, N);
    return OK;
}

// znowu ten paskudny wrapper, jakby nie bylo ich juz za duzo i tak
void* connect_wrapper(enum data_type_t type, int num_arrays, void** arrays_of_pointers_to_arrays) {
    if (num_arrays < 1 || num_arrays > 10) {
        return NULL;
    }

    switch (num_arrays) {
        case 1:
            return connect(type, 1, *(arrays_of_pointers_to_arrays + 0));
        case 2:
            return connect(type, 2, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1));
        case 3:
            return connect(type, 3, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2));
        case 4:
            return connect(type, 4, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2), *(arrays_of_pointers_to_arrays + 3));
        case 5:
            return connect(type, 5, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2), *(arrays_of_pointers_to_arrays + 3), *(arrays_of_pointers_to_arrays + 4));
        case 6:
            return connect(type, 6, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2), *(arrays_of_pointers_to_arrays + 3), *(arrays_of_pointers_to_arrays + 4), *(arrays_of_pointers_to_arrays + 5));
        case 7:
            return connect(type, 7, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2), *(arrays_of_pointers_to_arrays + 3), *(arrays_of_pointers_to_arrays + 4), *(arrays_of_pointers_to_arrays + 5), *(arrays_of_pointers_to_arrays + 6));
        case 8:
            return connect(type, 8, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2), *(arrays_of_pointers_to_arrays + 3), *(arrays_of_pointers_to_arrays + 4), *(arrays_of_pointers_to_arrays + 5), *(arrays_of_pointers_to_arrays + 6), *(arrays_of_pointers_to_arrays + 7));
        case 9:
            return connect(type, 9, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2), *(arrays_of_pointers_to_arrays + 3), *(arrays_of_pointers_to_arrays + 4), *(arrays_of_pointers_to_arrays + 5), *(arrays_of_pointers_to_arrays + 6), *(arrays_of_pointers_to_arrays + 7), *(arrays_of_pointers_to_arrays + 8));
        case 10:
            return connect(type, 10, *(arrays_of_pointers_to_arrays + 0), *(arrays_of_pointers_to_arrays + 1), *(arrays_of_pointers_to_arrays + 2), *(arrays_of_pointers_to_arrays + 3), *(arrays_of_pointers_to_arrays + 4), *(arrays_of_pointers_to_arrays + 5), *(arrays_of_pointers_to_arrays + 6), *(arrays_of_pointers_to_arrays + 7), *(arrays_of_pointers_to_arrays + 8), *(arrays_of_pointers_to_arrays + 9));
        default:
            return NULL;
    }
}

void destroy_arr_of_arrs(void** arr_of_arr, int N) {
    for (int i = 0; i < N; i++) {
        if (*(arr_of_arr + i) != NULL) { free(*(arr_of_arr + i));}
    }
    free(arr_of_arr);
}

void print_result(enum data_type_t type, void* result) {
    switch (type) {
        case data_type_short: {
            short* res = result;
            while (*res != -1) {
                printf("%hd ", *res);
                res++;
            }
            return;
        }
        case data_type_int: {
            int* res = result;
            while (*res != -1) {
                printf("%d ", *res);
                res++;
            }
            return;
        }
        case data_type_float: {
            float* res = result;
            while (*res != -1) {
                printf("%f ", *res);
                res++;
            }
            return;
        }
        case data_type_double: {
            double* res = result;
            while (*res != -1) {
                printf("%lf ", *res);
                res++;
            }
            return;
        }
        case data_type_long: {
            long* res = result;
            while (*res != -1) {
                printf("%ld ", *res);
                res++;
            }
            return;
        }
        default: break;
    }
}