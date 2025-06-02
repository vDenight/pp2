//
// Created by mrybczynski on 6/2/2025.
//

#include <stddef.h>
#include "word_count.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char* buffer = malloc(sizeof(char) * 50); // a buffer to store words from the file
    if (!buffer) {
        fclose(f);
        free(occur);
        if (err_code) *err_code = COUNT_ALLOC_FAIL;
        return NULL;
    }

    va_list words;
    va_start(words, N);

    int current_count;

    for (int i = 0; i < N; i++) {
        fseek(f, 0, SEEK_SET);
        char *word = va_arg(words, char*);
        current_count = 0;


        while (read_word_from_file(f, buffer, 50)) {
            if (strcmp(word, buffer) == 0) {
                current_count++;
            }
        }
        *(occur + i) = current_count;
    }


    va_end(words);
    fclose(f);
    free(buffer);
    return occur;
}

_Bool read_word_from_file(FILE* f, char* buffer, int max_len) {
    memset(buffer, '\0', max_len);
    int c;
    _Bool started = 0;
    int index = 0;
    while (1) {
        c = fgetc(f);
        if (c == EOF && !started) {
            return 0;
        }
        if (c == EOF || c == ' ' || c == ',' || c == '.' || c == '\n') {
            if (!started) continue;
            return 1;
        }

        started = 1;
        *(buffer + index) = (char) c;
        index++;
        if (index >= max_len) return 1;
    }
}
