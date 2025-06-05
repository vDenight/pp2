#include <stdio.h>
#include "bit_compar.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1
};

int main(void) {
    int a, b;
    printf("Podaj dwie liczby: ");
    if (!scanf("%d", &a)) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (!scanf("%d", &b)) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (is_equal(a, b)) printf("rowne\n");
    else printf("nierowne\n");

    if (is_negative(a)) printf("ujemna ");
    else printf("nieujemna ");

    if (is_negative(b)) printf("ujemna\n");
    else printf("nieujemna\n");

    return OK;
}