#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

void change_new_line_to_terminator(char* str);

int main(void) {

    char* buffer;
    buffer = calloc(1001, sizeof(char));
    if (!buffer) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    StringFuncPtr* funcs = calloc(4, sizeof(StringFuncPtr));
    if (!funcs) {
        free(buffer);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    *funcs = lower_to_upper;
    *(funcs + 1) = upper_to_lower;
    *(funcs + 2) = reverse_letter;
    *(funcs + 3) = space_to_dash;

    int* choices = calloc(4, sizeof(int));
    if (!choices) {
        free(buffer);
        free(funcs);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    // all alloced
    printf("Podaj tekst do przeksztalcenia: ");
    fgets(buffer, 1001, stdin);
    change_new_line_to_terminator(buffer);

    int N;
    printf("Podaj liczbe operacj do przeprowadzenia: ");
    if (scanf("%d", &N) != 1) {
        free(buffer);
        free(funcs);
        free(choices);
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (N < 2 || N > 4) {
        free(buffer);
        free(funcs);
        free(choices);
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    printf("Podaj wybrane operacje: ");
    for (int i = 0; i < N; i++) {
        if (scanf("%d", choices + i) != 1) {
            free(buffer);
            free(funcs);
            free(choices);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }
        if ((*(choices + i)) < 0 || (*(choices + i)) > 3) {
            free(buffer);
            free(funcs);
            free(choices);
            printf("Incorrect input data");
            return INCORRECT_INPUT_DATA;
        }
    }
    char** result = NULL;
    switch (N) {
        case 2:
            result = text_modifier(buffer, N, *(funcs + *(choices + 0)), *(funcs + *(choices + 1)));
            break;
        case 3:
            result = text_modifier(buffer, N, *(funcs + *(choices + 0)), *(funcs + *(choices + 1)), *(funcs + *(choices + 2)));
            break;
        case 4:
            result = text_modifier(buffer, N, *(funcs + *(choices + 0)), *(funcs + *(choices + 1)), *(funcs + *(choices + 2)), *(funcs + *(choices + 3)));
            break;
        default: break;
    }

    if (!result) {
        free(buffer);
        free(funcs);
        free(choices);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    // print result
    for (int i = 0; i < N; i++) {
        printf("%s\n", *(result + i));
    }

    free_texts(result);
    free(funcs);
    free(choices);
    free(buffer);
    return OK;
}

void change_new_line_to_terminator(char* str) {
    while (*str != '\n' && *str != '\0') {
        str++;
    }
    *str = '\0';
}
