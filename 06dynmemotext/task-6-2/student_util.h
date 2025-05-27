//
// Created by mcihal on 26.05.25.
//

#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H

struct student_t {
    char* name;
    char* surname;
    int index;
};

struct student_t* read(int *err_code);
void show(const struct student_t* p);

void destroy(struct student_t **s);

enum read_code {
    READ_OK = 0,
    READ_WRONG_INPUT = 1,
    READ_ONLY_NAME = 2,
    READ_ONLY_NAME_SURNAME = 3,
    READ_ALLOC_FAIL = 4
};

#endif //STUDENT_UTIL_H
