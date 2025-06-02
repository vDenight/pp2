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

_Bool is_delimiter(int c) {
    return c == EOF || isspace(c) || c == ',' || c == '.';
}

int consume_delimiters_and_get_first_word_char(FILE *file) {
    int c;
    do {
        c = fgetc(file);
    } while (c != EOF && is_delimiter(c)); // Consume all delimiters

    return c; // Returns the first non-delimiter char, or EOF
}

_Bool char_is_string_end(int c) {
    if (c == EOF || c == '\n' || c == ' ' || c == '\t' || c == '.' || c == ',') return 1;
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
            while (!char_is_string_end(c = fgetc(f))) {
                if (is_correct == 1) { is_correct = -1;} // this means that it was longer for example ax and axe, because the loop should already terminate
                if (is_correct == 0) {
                    if (*(word + current_index) == c) {
                        current_index++;
                        if (current_index == str_len - 2) {
                            is_correct = 1;
                        }
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

// _Bool read_word_from_file(FILE* f, char* buffer, int max_len) {
//     memset(buffer, '\0', max_len);
//     int c;
//     _Bool started = 0;
//     int index = 0;
//     while (1) {
//         c = fgetc(f);
//         if (c == EOF && !started) {
//             return 0;
//         }
//         if (c == EOF || c == ' ' || c == ',' || c == '.' || c == '\n') {
//             if (!started) continue;
//             return 1;
//         }
//
//         started = 1;
//         *(buffer + index) = (char) c;
//         index++;
//         if (index >= max_len) return 1;
//     }
// }
