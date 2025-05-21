//
// Created by mcihal on 21.05.25.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

struct word_count_t {
    char *word;
    int counter;
};

struct dictionary_t
{
    int size;
    int capacity;
    struct word_count_t *wc;
};

struct dictionary_t* create_dictionary(int N, int *err_code);
void destroy_dictionary(struct dictionary_t** d);

int dictionary_add_word(struct dictionary_t *d, const char *word);
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word);

void dictionary_display(const struct dictionary_t *d);

_Bool expand_dictionary(struct dictionary_t *d);

enum create_code {
    CREATE_OK = 0,
    CREATE_ALLOC_FAIL = 2,
    CREATE_INPUT_ERROR = 1
};

enum add_code {
    ADD_OK = 0,
    ADD_INPUT_ERROR = 1,
    ADD_ALLOC_FAIL = 2
};

#endif //DICTIONARY_H
