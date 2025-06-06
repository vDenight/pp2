#include <stdint.h>
#include <stdio.h>

#include "functions.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2
};

int main(void) {

    int d_type;

    printf("Enter data type: ");
    if (scanf("%d", &d_type) != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (d_type < 0 || d_type > 2) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    int num_set;
    int num_cleared;

    printf("Enter an integer number: ");
    switch (d_type) {
        case 0: {
            unsigned int num = {0};
            if (scanf("%u", &num) != 1) {
                printf("Incorrect input");
                return INCORRECT_INPUT;
            }
            COUNT_BITS(num, &num_set, &num_cleared);
            printf("%d\n%d\n", num_set, num_cleared);
            DISPLAY_BITS(num);
            printf("\n");
            REVERSE_BITS(&num);
            DISPLAY_BITS(num);
            break;
        }
        case 1: {
            unsigned short num = {0};
            if (scanf("%hu", &num) != 1) {
                printf("Incorrect input");
                return INCORRECT_INPUT;
            }
            COUNT_BITS(num, &num_set, &num_cleared);
            printf("%d\n%d\n", num_set, num_cleared);
            DISPLAY_BITS(num);
            printf("\n");
            REVERSE_BITS(&num);
            DISPLAY_BITS(num);
            break;
        }
        case 2: {
            uint64_t num = {0};
            if (scanf("%lu", &num) != 1) {
                printf("Incorrect input");
                return INCORRECT_INPUT;
            }
            COUNT_BITS(num, &num_set, &num_cleared);
            printf("%d\n%d\n", num_set, num_cleared);
            DISPLAY_BITS(num);
            printf("\n");
            REVERSE_BITS(&num);
            DISPLAY_BITS(num);
            break;
        }
        default: return 2137;
    }

    return OK;
}
