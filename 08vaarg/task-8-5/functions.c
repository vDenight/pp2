//
// Created by mrybczynski on 6/4/2025.
//

#include <stdio.h>
#include "functions.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char** text_modifier(const char* text, int N, ...) {
    if (text == NULL || N < 1) return NULL;

    char** result = calloc(N + 1, sizeof(char*));
    if (!result) return NULL;

    //initialize va_list
    va_list functions;
    va_start(functions, N);

    for (int i = 0; i < N; i++) {
        StringFuncPtr func = va_arg(functions, StringFuncPtr);
        *(result+i) = func(text);
        if (!(*(result+i))) {
            va_end(functions);
            free_texts(result);
            return NULL;
        }
    }

    va_end(functions);
    return result;
}

char* lower_to_upper(const char *in) {
    if (!in) return NULL;

    char* res = calloc(strlen(in) + 1, sizeof(char));
    if (!res) return NULL;

    for (int i = 0; i < (int) strlen(in); i++) {
        *(res + i) = (char) toupper(*(in + i));
    }

    return res;
}

char* upper_to_lower(const char *in) {
    if (!in) return NULL;

    char* res = calloc(strlen(in) + 1, sizeof(char));
    if (!res) return NULL;

    for (int i = 0; i < (int) strlen(in); i++) {
        *(res + i) = (char) tolower(*(in + i));
    }

    return res;
}

char* space_to_dash(const char *in) {
    if (!in) return NULL;

    char* res = calloc(strlen(in) + 1, sizeof(char));
    if (!res) return NULL;

    for (int i = 0; i < (int) strlen(in); i++) {
        if (*(in + i) == ' ') {
            *(res + i) = '_';
        } else {
            *(res + i) = *(in + i);
        }
    }

    return res;
}

char reverse_char(char c);

char* reverse_letter(const char *in) {
    if (!in) return NULL;

    char* res = calloc(strlen(in) + 1, sizeof(char));
    if (!res) return NULL;

    for (int i = 0; i < (int) strlen(in); i++) {
        *(res + i) = reverse_char(*(in + i));
    }

    return res;
}

char reverse_char(char c) {
    if (!isalpha(c)) return c;

    if (isupper(c)) {
        return (char) ('Z' - c + 'A'); // uppercase
    }

    return (char) ('z' - c + 'a'); // lowercase
}

void free_texts(char **texts) {
    if (!texts) return;
    char** temp = texts;
    while (*temp) {
        free(*temp);
        temp++;
    }
    free(texts);
}

