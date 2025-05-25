#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_util.h"

enum main_code {
    OK = 0,
    ALLOC_FAIL = 8
};

_Bool check_for_alpha(char* buffer);

int main(void) {

    char* buffer = calloc(1000, sizeof(char));
    if (!buffer) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Enter text: ");
    fgets(buffer, 1000, stdin);

    if (!check_for_alpha(buffer)) {
        free(buffer);
        printf("Nothing to show");
        return OK;
    }

    char** words = split_words(buffer);
    if (!words) {
        free(buffer);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    sort_words(words);
    display(words);

    destroy(words);
    free(buffer);

    return OK;
}

_Bool check_for_alpha(char* buffer) {
    while (*buffer) {
        if (isalpha(*buffer)) {
            return 1;
        }
        buffer++;
    }
    return 0;
}