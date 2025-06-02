//
// Created by mrybczynski on 6/2/2025.
//

#include <stddef.h>
#include "word_count.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool move_to_next_word(FILE* f) {
    while (1) {
        int c = fgetc(f);
        if (c == EOF) return 0;
        if (c == ' ' || c == '\t' || c == '\n' || c == '.' || c == ',' || c == '"' || c == '-' || c == '\''
            || c == '?' || c == '!') continue;

        fseek(f, -1, SEEK_CUR);
        return 1;
    }
}

_Bool char_is_string_end(int c) {
    if (c == EOF || c == '\n' || c == ' ' || c == '\t' || c == '.' || c == ',' || c == '"' || c == '-' || c == '\''
        || c == '?' || c == '!') return 1;
    return 0;
}

int* count_words(const char *filename, int *err_code, int N, ...) {
    if (filename == NULL || N < 1) {
        if (err_code) *err_code = COUNT_WRONG_INPUT;
        return NULL;
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        if (err_code) *err_code = COUNT_CANNOT_OPEN_FILE;
        return NULL;
    }

    int* occur = malloc(sizeof(int) * N);
    if (!occur) {
        fclose(f);
        if (err_code) *err_code = COUNT_ALLOC_FAIL;
        return NULL;
    }

    va_list words;
    va_start(words, N);

    int current_count;

    for (int i = 0; i < N; i++) {
        int c;

        fseek(f, 0, SEEK_SET);
        char *word = va_arg(words, char*);
        current_count = 0;
        int str_len = (int)strlen(word);
        int current_index = 0;
        int is_correct = 0; // -1 means not correct, 0 we dont know, 1 it is very likely correct

        while (move_to_next_word(f)) {
            is_correct = 0;
            current_index = 0;
            while (!char_is_string_end(c = fgetc(f))) {
                if (is_correct == 1) { is_correct = -1;} // this means that it was longer for example ax and axe, because the loop should already terminate
                if (is_correct == 0) {
                    if (*(word + current_index) == c) {
                        if (current_index == str_len - 1) {
                            is_correct = 1;
                        }
                        current_index++;
                    } else {
                        is_correct = -1;
                    }
                }
            }
            if (is_correct == 1) {
                current_count++;
            }
        }
        *(occur + i) = current_count;
    }


    va_end(words);
    fclose(f);
    if (err_code) *err_code = COUNT_OK;
    return occur;
}
