//
// Created by mcihal on 26.05.25.
//

#include "student_util.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct student_t* read(struct student_t* p, int *err_code) {

    if (!p) {if (err_code) *err_code = READ_WRONG_INPUT; return NULL;}


    int c;
    // delete the spaces at the start
    while ((c = getchar()) == ' ' || c == '\t') {}

    _Bool started = 0;
    _Bool finished = 0;

    memset(p, 0, sizeof(*p)); // set the whole structure to zeros

    // read the name
    for (int i = 0; i < 19; i++) {
        if (c == ',') {finished = 1; break;}
        if (c == '\n' || c == EOF) {if (err_code) *err_code = READ_WRONG_INPUT; return NULL;}

        *(p->name + i) = (char) c;
        started = 1;
        c = getchar();
    }
    if (!finished) if (c == ',') finished = 1;

    // no name
    if (!started || !finished) {if (err_code) *err_code = READ_WRONG_INPUT; return NULL;}

    // now the surname
    // lets get the spaces again
    while ((c = getchar()) == ' ' || c == '\t') {}

    started = 0;
    finished = 0;

    for (int i = 0; i < 39; i++) {
        if (c == ',') {finished = 1; break;}
        if (c == '\n' || c == EOF) {if (err_code) *err_code = READ_ONLY_NAME; return NULL;}

        *(p->surname + i) = (char) c;
        started = 1;
        c = getchar();
    }

    if (!finished) if (c == ',') finished = 1;
    if (!started || !finished) {if (err_code) *err_code = READ_ONLY_NAME; return NULL;}

    // now the index
    int scanf_val = scanf("%d", &(p->index));

    if (scanf_val != 1) {if (err_code) *err_code = READ_ONLY_NAME_SURNAME; return NULL;}

    if (err_code) *err_code = READ_OK;
    return p;
}

void show(const struct student_t* p) {
    if (!p) return;
    printf("%s %s, %d" , p->name , p->surname, p->index);
}
