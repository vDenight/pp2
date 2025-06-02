//
// Created by mrybczynski on 6/2/2025.
//

#ifndef WORD_COUNT_H
#define WORD_COUNT_H
#include <stdio.h>

int* count_words(const char *filename, int *err_code, int N, ...);

// helper to read words from file
_Bool read_word_from_file(FILE* f, char* buffer, int max_len);

enum count_code {
    COUNT_OK = 0,
    COUNT_WRONG_INPUT = 1,
    COUNT_CANNOT_OPEN_FILE = 2,
    COUNT_ALLOC_FAIL = 3
};

#endif //WORD_COUNT_H
