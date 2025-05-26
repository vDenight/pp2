//
// Created by mcihal on 26.05.25.
//

#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H

struct student_t {
    char name[20];
    char surname[40];
    int index;
};

struct student_t* read(struct student_t* p, int *err_code);
void show(const struct student_t* p);

enum read_code {
    READ_OK = 0,
    READ_WRONG_INPUT = 1,
    READ_ONLY_NAME = 2,
    READ_ONLY_NAME_SURNAME = 3
};

#endif //STUDENT_UTIL_H
