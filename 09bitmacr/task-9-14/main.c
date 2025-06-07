#include <stdio.h>
#include "functions.h"

CREATE_READ_FUNCTIONS(int, "%d")
CREATE_SORT_FUNCTIONS(int)
CREATE_DISPLAY_FUNCTIONS(int, "%d")

CREATE_READ_FUNCTIONS(float, "%f")
CREATE_SORT_FUNCTIONS(float)
CREATE_DISPLAY_FUNCTIONS(float, "%f")

CREATE_READ_FUNCTIONS(double, "%lf")
CREATE_SORT_FUNCTIONS(double)
CREATE_DISPLAY_FUNCTIONS(double, "%lf")

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

enum type {
    INT = 0,
    FLOAT = 1,
    DOUBLE = 2
};

int main(void) {

    int type;
    printf("Choose your type: ");
    if (scanf("%d", &type) != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (type < 0 || type > 2) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    int size;
    printf("Podaj rozmiar tablicy: ");
    if (scanf("%d", &size) != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (size < 0) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    switch (type) {
        case INT: {
            int* tab = calloc(size, sizeof(int));
            if (!tab) {
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }

            printf("Podaj liczby: ");
            int read_val = read_int(tab, size);
            if (read_val == 2) {
                free(tab);
                printf("Incorrect input");
                return INCORRECT_INPUT;
            }

            sort_int(tab, size);
            display_int(tab, size);
            free(tab);
            break;
        }
        case FLOAT: {
            float* tab = calloc(size, sizeof(float));
            if (!tab) {
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }

            printf("Podaj liczby: ");
            int read_val = read_float(tab, size);
            if (read_val == 2) {
                free(tab);
                printf("Incorrect input");
                return INCORRECT_INPUT;
            }

            sort_float(tab, size);
            display_float(tab, size);
            free(tab);
            break;
        }
        case DOUBLE: {
            double* tab = calloc(size, sizeof(double));
            if (!tab) {
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }

            printf("Podaj liczby: ");
            int read_val = read_double(tab, size);
            if (read_val == 2) {
                free(tab);
                printf("Incorrect input");
                return INCORRECT_INPUT;
            }

            sort_double(tab, size);
            display_double(tab, size);
            free(tab);
            break;
        }
        default: return 2137;
    }


    return 0;
}