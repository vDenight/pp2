//
// Created by mcihal on 25.05.25.
//

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "word_util.h"

#include <stdio.h>

char* get_word(const char *text, char** text_end, int* error);

char **split_words(const char *text) {
    char* text_to_get_word = (char*) text;
    char* text_after_getting = NULL;
    int err = 0;
    int size = 0;

    // for now only a null then we will realloc
    char** words = calloc(1, sizeof(char*));
    if (!words) return NULL;

    while (1) {
        char *new_word = get_word(text_to_get_word, &text_after_getting, &err);
        if (new_word == NULL && !err) break;
        if (err) {
            destroy(words);
            return NULL;
        }
        size++;
        char** temp = realloc(words, (size + 1) * sizeof(char*));
        if (!temp) {
            free(new_word);
            destroy(words);
            return NULL;
        }
        words = temp;

        // switching NULL with new word
        *(words + size) = NULL;
        *(words + size - 1) = new_word;

        // setting text to get word, for the next iteration
        text_to_get_word = text_after_getting;
    }
    if (*words == NULL) {
        destroy(words);
        return NULL;
    }
    return words;
}

// the function will return the pointer to the new word and will change text end to the rest of the text if provided
char* get_word(const char *text, char** text_end, int* error) {

    char* text_cursor = (char*) text;
    _Bool started = 0;
    char* word_start = (char*) text;
    int strlen = 0;
    if (error) *error = 0;

    while (1) {
        if (isalpha(*text_cursor)) {
            if (!started) {
                word_start = text_cursor;
                started = 1;
            }
            text_cursor++;
            strlen++;
        } else {
            if (!started && *text_cursor == '\0') return NULL;
            if (!started) text_cursor++;
            else {
                break;
            }
        }
    }

    char *new_word = calloc(strlen + 1, 1);
    if (!new_word) {
        if (error) *error = 1;
        return NULL;
    }

    memcpy(new_word, word_start, strlen);
    if (text_end) *text_end = text_cursor;

    return new_word;
}

int words_get_size(char **words) {
    int size = 0;
    while (*words) {
        size++;
        words++;
    }
    return size;
}

int compare_strings(const void* s1, const void* s2) {
    return strcmp(*(char**)s1, *(char**)s2);
}

int sort_words(char **words) {
    if (!words) return SORT_ERROR;
    int words_size = words_get_size(words);
    qsort(words, words_size, sizeof(char*), compare_strings);
    return SORT_OK;
}

void destroy(char **words) {
    if (words == NULL) {
        return;
    }

    int size = words_get_size(words);
    for (int i = 0; i < size; i++) {
        free(*(words + i));
    }
    free(words);
}

void display(char **words) {
    if (words) {
        while (*words) {
            printf("%s\n", *words);
            words++;
        }
    }
}
