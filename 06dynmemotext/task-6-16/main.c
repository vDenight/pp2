#include <stdio.h>
#include <stdlib.h>

#include "crosswords.h"

enum main_return_code {
    MAIN_OK = 0,
    MAIN_INCORRECT_INPUT = 1,
    MAIN_ALLOC_FAIL = 8,
};

int main(void) {

    char** double_cross = NULL, **first_cross = NULL, **second_cross = NULL;

    char* in1 = NULL, *in2 = NULL, *in3 = NULL, *in4 = NULL;
    in1 = calloc(11, sizeof(char));
    in2 = calloc(11, sizeof(char));
    in3 = calloc(11, sizeof(char));
    in4 = calloc(11, sizeof(char));
    if (in1 == NULL || in2 == NULL || in3 == NULL || in4 == NULL) {
        if (in1) free(in1);
        if (in2) free(in2);
        if (in3) free(in3);
        if (in4) free(in4);
        printf("Failed to allocate memory");
        return MAIN_ALLOC_FAIL;
    }

    printf("Enter words: ");
    scanf("%10s %10s %10s %10s", in1, in2, in3, in4);

    const int ret_val = create_double_leading_word_cross(in1, in2, in3, in4,
        &double_cross, &first_cross, &second_cross);

    enum main_return_code main_return_code = MAIN_OK;

    switch (ret_val) {
        case DCREATE_OK:
            display(first_cross);
            printf("\n");
            display(second_cross);
            printf("\n");
            display(double_cross);
            break;
        case DCREATE_ALLOC_FAIL:
            printf("Failed to allocate memory");
            main_return_code = MAIN_ALLOC_FAIL;
            break;
        case DCREATE_CANT_CROSS:
            printf("Unable to make two crosses");
            break;
        case DCREATE_WRONG_INPUT:
            printf("Incorrect input");
            main_return_code = MAIN_INCORRECT_INPUT;
            break;
        default: break;
    }

    free(in1);
    free(in2);
    free(in3);
    free(in4);
    if (ret_val == DCREATE_OK) {
        destroy(first_cross);
        destroy(second_cross);
        destroy(double_cross);
    }
    return main_return_code;
}