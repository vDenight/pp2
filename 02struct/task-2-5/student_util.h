//
// Created by mcihal on 26.05.25.
//

#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H

struct student_t {
    char name[20];
    char surname[40];
    int index;
    char field[50];
    char faculty[80];
    int year;
};

struct student_t* read(struct student_t* p, int *err_code);
void display(const struct student_t* p);
struct student_t* set(struct student_t* student, const char * name,
                      const char * surname, int index,
                      const char * field, const char * faculty,
                      int year, int *err_code);

void display_name(const struct student_t* student);
void display_surname(const struct student_t* student);
void display_index(const struct student_t* student);
void display_field(const struct student_t* student);
void display_faculty(const struct student_t* student);
void display_year(const struct student_t* student);

int save_student_b(const char *filename, const struct student_t* s);
int load_student_b(const char *filename, struct student_t* s);
int save_student_t(const char *filename, const struct student_t* s);
int load_student_t(const char *filename, struct student_t* s);

enum read_code {
    READ_OK = 0,
    READ_WRONG_INPUT = 1,
    READ_ONLY_NAME = 2,
    READ_ONLY_NAME_SURNAME = 3,
    READ_ONLY_NAME_SURNAME_INDEX = 4,
    READ_TO_FIELD = 5,
    READ_TO_FACULTY = 6
};

enum file_code {
    FILE_OK = 0,
    FILE_WRONG_INPUT = 1,
    FILE_CANNOT_OPEN_FILE = 2,
    FILE_FILE_CORRUPTED = 3
};

#endif //STUDENT_UTIL_H
