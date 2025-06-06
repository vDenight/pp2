#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

DEFINE_ARRAY(int)
CREATE_ARRAY(int)
FREE_ARRAY(int)
SAVE_ARRAY(int)
LOAD_ARRAY(int)
SORT_ARRAY(int)

DEFINE_ARRAY(double)
CREATE_ARRAY(double)
FREE_ARRAY(double)
SAVE_ARRAY(double)
LOAD_ARRAY(double)
SORT_ARRAY(double)

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    COULD_NOT_OPEN_FILE = 4,
    COULD_NOT_CREATE_FILE = 5,
    FILE_CORRUPTED = 6,
    ALLOC_FAIL = 8
};

enum data_type {
    INT = 0,
    DOUBLE = 1
};

int main(void) {

    char* buffer = calloc(31, sizeof(char));
    if (!buffer) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }
    printf("Enter filename: ");
    scanf("%30s", buffer);

    int d_type;
    printf("Choose your type: ");
    if (!scanf("%d", &d_type)) {
        free(buffer);
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    switch (d_type) {
        case INT: {
            struct array_int_t* arr;
            int load_res = load_array_int(&arr, buffer);
            if (load_res == 2) {
                free(buffer);
                printf("Couldn't open file");
                return COULD_NOT_OPEN_FILE;
            }
            if (load_res == 3) {
                free(buffer);
                printf("File corrupted");
                return FILE_CORRUPTED;
            }
            if (load_res == 4) {
                free(buffer);
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }
            sort_array_int(arr);
            int save_res = save_array_int(arr, buffer);
            if (save_res == 2) {
                free_array_int(arr);
                free(buffer);
                printf("Couldn't create file");
                return COULD_NOT_CREATE_FILE;
            }
            free_array_int(arr);
            break;
        }
        case DOUBLE: {
            struct array_double_t* arr;
            int load_res = load_array_double(&arr, buffer);
            if (load_res == 2) {
                free(buffer);
                printf("Couldn't open file");
                return COULD_NOT_OPEN_FILE;
            }
            if (load_res == 3) {
                free(buffer);
                printf("File corrupted");
                return FILE_CORRUPTED;
            }
            if (load_res == 4) {
                free(buffer);
                printf("Failed to allocate memory");
                return ALLOC_FAIL;
            }
            sort_array_double(arr);
            int save_res = save_array_double(arr, buffer);
            if (save_res == 2) {
                free_array_double(arr);
                free(buffer);
                printf("Couldn't create file");
                return COULD_NOT_CREATE_FILE;
            }
            free_array_double(arr);
            break;
        }
        default: {
            free(buffer);
            printf("Incorrect input data");
            return INCORRECT_INPUT_DATA;
        }
    }

    printf("File saved");
    free(buffer);
    return OK;
}
