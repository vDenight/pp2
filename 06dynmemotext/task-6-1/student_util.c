//
// Created by mcihal on 26.05.25.
//

#include "student_util.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_t* read(int *err_code) {

    struct student_t* student = calloc(1, sizeof(struct student_t));
    if (!student) {
        if (err_code) *err_code = READ_ALLOC_FAIL;
        return NULL;
    }

    printf("Podaj dane: ");

    int c;
    // delete the spaces at the start
    while ((c = getchar()) == ' ' || c == '\t') {}

    _Bool started = 0;
    _Bool finished = 0;

    // read the name
    for (int i = 0; i < 19; i++) {
        if (c == ',') {finished = 1; break;}
        if (c == '\n' || c == EOF) {if (err_code) *err_code = READ_WRONG_INPUT; free(student); return NULL;}

        *(student->name + i) = (char) c;
        started = 1;
        c = getchar();
    }
    if (!finished) if (c == ',') finished = 1;

    // no name
    if (!started || !finished) {if (err_code) *err_code = READ_WRONG_INPUT; free(student); return NULL;}

    // now the surname
    // lets get the spaces again
    while ((c = getchar()) == ' ' || c == '\t') {}

    started = 0;
    finished = 0;

    for (int i = 0; i < 39; i++) {
        if (c == ',') {finished = 1; break;}
        if (c == '\n' || c == EOF) {if (err_code) *err_code = READ_ONLY_NAME; free(student); return NULL;}

        *(student->surname + i) = (char) c;
        started = 1;
        c = getchar();
    }

    if (!finished) if (c == ',') finished = 1;
    if (!started || !finished) {if (err_code) *err_code = READ_ONLY_NAME; free(student); return NULL;}

    // now the index
    int scanf_val = scanf("%d", &(student->index));

    if (scanf_val != 1) {if (err_code) *err_code = READ_ONLY_NAME_SURNAME; free(student); return NULL;}

    if (err_code) *err_code = READ_OK;
    return student;
}

void show(const struct student_t* p) {
    if (!p) return;
    printf("%s %s, %d" , p->name , p->surname, p->index);
}

void destroy(struct student_t **s) {
    if (!s) return;
    if (!(*s)) return;

    free(*s);
    *s = NULL;
}
