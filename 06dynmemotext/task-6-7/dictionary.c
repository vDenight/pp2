//
// Created by mcihal on 21.05.25.
//

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dictionary_t* create_dictionary(int N, int *err_code) {
    if (N < 1) {
        if (err_code) *err_code = CREATE_INPUT_ERROR;
        return NULL;
    }

    struct dictionary_t* my_dict = malloc(sizeof(struct dictionary_t));
    if (my_dict == NULL) {
        if (err_code) *err_code = CREATE_ALLOC_FAIL;
        return NULL;
    }

    my_dict->wc = calloc(sizeof(struct word_count_t), N);
    if (my_dict->wc == NULL) {
        if (err_code) *err_code = CREATE_ALLOC_FAIL;
        free(my_dict);
        return NULL;
    }

    my_dict->capacity = N;
    my_dict->size = 0;

    if (err_code) *err_code = CREATE_OK;
    return my_dict;
}

void destroy_dictionary(struct dictionary_t** d) {
    if (d == NULL || *d == NULL || (*d)->wc == NULL || (*d)->size < 0 || (*d)->capacity < 1) return;
    for (int i = 0; i < (*d)->size; i++) {
        if (((*d)->wc + i)->word != NULL) { // check if the word is null
            free(((*d)->wc + i)->word); // if not null free the word
            ((*d)->wc + i)->word = NULL; // set to null just in case
        }
    }
    free((*d)->wc);
    free(*d);
    *d = NULL;
}

struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word) {
    if (d == NULL || d->wc == NULL || d->size < 0 || d->capacity < 1) return NULL;
    for (int i = 0; i < d->size; i++) {
        if (strcmp(word, ((d->wc) + i)->word) == 0) return d->wc + i;
    }
    return NULL;
}

int dictionary_add_word(struct dictionary_t *d, const char *word) {
    if (d == NULL || d->wc == NULL || d->size < 0 || d->capacity < 1) return ADD_INPUT_ERROR;

    // check if the word is already present
    struct word_count_t* w_count = dictionary_find_word(d, word);
    if (w_count != NULL) {
        w_count->counter++;
        return ADD_OK;
    }

    // not present dup the word
    char* new_word = strdup(word);
    if (new_word == NULL) return ADD_ALLOC_FAIL;

    // expand in case there is no space
    if (d->size >= d->capacity) {
        free(new_word);
        if (!expand_dictionary(d)) return ADD_ALLOC_FAIL;
    }

    // set the values respectively
    (d->wc + d->size) -> word = new_word;
    (d->wc + d->size) -> counter = 1;
    d->size++;

    return ADD_OK;
}

_Bool expand_dictionary(struct dictionary_t *d) {
    struct word_count_t* temp = realloc(d->wc, d->capacity * 2 * sizeof(struct word_count_t));
    if (temp == NULL) {
        return 0;
    }
    d->wc = temp;
    d->capacity *= 2;
    return 1;
}

void dictionary_display(const struct dictionary_t *d) {
    if (d == NULL || d->wc == NULL || d->size < 0 || d->capacity < 1) return;
    for (int i = 0; i < d->size; i++) {
        printf("%s %d\n", (d->wc + i)->word, (d->wc + i)->counter);
    }
}
