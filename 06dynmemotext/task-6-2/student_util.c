//
// Created by mcihal on 26.05.25.
//

#include "student_util.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_newline_with_terminator(char* buffer);
void strip_space(char* part);
_Bool str_to_int(char* str, int* integer);

struct student_t* read(int *err_code) {

    // first alloc the buffer
    char* buffer = calloc(100, sizeof(char));
    if (!buffer) {
        if (err_code) *err_code = READ_ALLOC_FAIL;
        return NULL;
    }

    // now alloc the strcut
    struct student_t* student = calloc(1, sizeof(struct student_t));
    if (!student) {
        if (err_code) *err_code = READ_ALLOC_FAIL;
        free(buffer);
        return NULL;
    }

    printf("Podaj dane: ");

    fgets(buffer, 100, stdin);
    replace_newline_with_terminator(buffer);

    char* name_part = strtok(buffer, ",");
    char* surname_part = strtok(NULL, ",");
    char* index_part = strtok(NULL, ",");

    if (name_part) strip_space(name_part);
    if (surname_part) strip_space(surname_part);
    if (index_part) strip_space(index_part);

    if (name_part == NULL || surname_part == NULL || strlen(name_part) == 0) {
        free(student);
        free(buffer);
        if (err_code) *err_code = READ_WRONG_INPUT;
        return NULL;
    }

    // now we alloc
    student->name = strdup(name_part);
    if (!student->name) {
        free(buffer);
        free(student);
        if (err_code) *err_code = READ_ALLOC_FAIL;
        return NULL;
    }

    if (index_part == NULL || strlen(surname_part) == 0) {
        free(student->name);
        free(student);
        free(buffer);
        if (err_code) *err_code = READ_ONLY_NAME;
        return NULL;
    }

    student->surname = strdup(surname_part);
    if (!student->surname) {
        free(student->name);
        free(student);
        free(buffer);
        if (err_code) *err_code = READ_ALLOC_FAIL;
        return NULL;
    }

    if (strlen(index_part) == 0) {
        free(student->name);
        free(student->surname);
        free(student);
        free(buffer);
        if (err_code) *err_code = READ_ONLY_NAME_SURNAME;
        return NULL;
    }

    if (!str_to_int(index_part, &(student->index))) {
        free(student->name);
        free(student->surname);
        free(student);
        free(buffer);
        if (err_code) *err_code = READ_ONLY_NAME_SURNAME;
        return NULL;
    }

    if (err_code) *err_code = READ_OK;
    free(buffer);
    return student;
}

_Bool str_to_int(char* str, int* integer) {
    *integer = 0;
    for (int i = 0; i < (int) strlen(str); i++) {
        if (isdigit(*(str + i))) {
            *integer = *integer * 10 + (*(str + i) - '0');
        } else {
            return 0;
        }
    }
    return 1;
}

void replace_newline_with_terminator(char* buffer) {
    for (int i = 0; i < 100; i++) {
        if (*(buffer + i) == '\n') {
            *(buffer + i) = '\0';
            return;
        }
    }
}

void strip_space(char* part) {
    int len = (int) strlen(part);
    int first_char_index = 0;
    int last_char_index = len - 1;

    while (first_char_index < len && isspace(*(part + first_char_index))) {
        first_char_index++;
    }

    if (first_char_index == len) {
        *part = '\0';
        return;
    }

    while (last_char_index > first_char_index && isspace(*(part + last_char_index))) {
        last_char_index--;
    }

    int new_len = last_char_index - first_char_index + 1;

    if (first_char_index > 0) {
        memmove(part, part + first_char_index, new_len);
    }

    *(part + new_len) = '\0';
}

void show(const struct student_t* p) {
    if (!p) return;
    printf("%s %s, %d" , p->name , p->surname, p->index);
}

void destroy(struct student_t **s) {
    if (!s) return;
    if (!(*s)) return;
    if ((*s)->name) free((*s)->name);
    if ((*s)->surname) free((*s)->surname);

    free(*s);
    *s = NULL;
}
