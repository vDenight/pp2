//
// Created by mcihal on 26.05.25.
//

#include "student_util.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

_Bool readnum(int *num);

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
    if (!readnum(&(p->index))) {if (err_code) *err_code = READ_ONLY_NAME_SURNAME; return NULL;}

    // now adding field
    // skip spaces
    while ((c = getchar()) == ' ' || c == '\t') {}

    started = 0;
    finished = 0;

    for (int i = 0; i < 49; i++) {
        if (c == ',') {finished = 1; break;}
        if (c == '\n' || c == EOF) {if (err_code) *err_code = READ_ONLY_NAME_SURNAME_INDEX; return NULL;}

        *(p->field+ i) = (char) c;
        started = 1;
        c = getchar();
    }

    if (!finished) if (c == ',') finished = 1;
    if (!started || !finished) {if (err_code) *err_code = READ_ONLY_NAME_SURNAME_INDEX; return NULL;}


    // skip spaces, add faculty
    while ((c = getchar()) == ' ' || c == '\t') {}

    started = 0;
    finished = 0;

    for (int i = 0; i < 79; i++) {
        if (c == ',') {finished = 1; break;}
        if (c == '\n' || c == EOF) {if (err_code) *err_code = READ_TO_FIELD; return NULL;}

        *(p->faculty+ i) = (char) c;
        started = 1;
        c = getchar();
    }

    if (!finished) if (c == ',') finished = 1;
    if (!started || !finished) {if (err_code) *err_code = READ_TO_FIELD; return NULL;}

    // now the year
    if (!readnum(&(p->year))) {if (err_code) *err_code = READ_TO_FACULTY; return NULL;}

    if (err_code) *err_code = READ_OK;
    return p;
}

_Bool is_vowel(char c);

void display(const struct student_t* p) {
    if (!p) return;
    if (is_vowel(*(p->field)))
    printf("%s %s, index number: %d, was an %s student at the %s in %d.\n"
        , p->name, p->surname, p->index, p->field, p->faculty, p->year);
    else
        printf("%s %s, index number: %d, was a %s student at the %s in %d.\n"
        , p->name, p->surname, p->index, p->field, p->faculty, p->year);
}

_Bool is_vowel(char c) {
    int c_up = toupper(c);
    if (c_up == 'A' || c_up == 'E' || c_up == 'I' || c_up == 'O' || c_up == 'U') return 1;
    return 0;
}

struct student_t* set(struct student_t* student, const char * name,
                      const char * surname, int index,
                      const char * field, const char * faculty,
                      int year, int *err_code) {
    if (!student || !name || ! surname || !field || !faculty) {
        if (err_code) *err_code = 1;
        return NULL;
    }

    if (strlen(name) > 19 || strlen(surname) > 39 || strlen(field) > 49 || strlen(faculty) > 79) {
        if (err_code) *err_code = 1;
        return NULL;
    }

    strcpy(student->name, name);
    strcpy(student->surname, surname);
    strcpy(student->field, field);
    strcpy(student->faculty, faculty);
    student->index = index;
    student->year = year;

    if (err_code) *err_code = 0;
    return student;

}

void display_name(const struct student_t* student) {
    if (!student) return;
    printf("Student name: %s\n", student->name);
}
void display_surname(const struct student_t* student) {
    if (!student) return;
    printf("Student surname: %s\n", student->surname);
}
void display_index(const struct student_t* student) {
    if (!student) return;
    printf("Index: %d\n", student->index);
}
void display_field(const struct student_t* student) {
    if (!student) return;
    printf("Field: %s\n", student->field);
}
void display_faculty(const struct student_t* student) {
    if (!student) return;
    printf("Faculty: %s\n", student->faculty);
}
void display_year(const struct student_t* student) {
    if (!student) return;
    printf("Year: %d\n", student->year);
}

_Bool readnum(int* num) {
    int c;
    *num = 0;
    _Bool started = 0;
    while (1) {
        c = getchar();
        if ((c == '\n' || c == ',' || c == EOF) && !started) return 0;
        if (c == '\n' || c == ',' || c == EOF) return 1;

        if (c == ' ' && !started) continue;
        if (isdigit(c)) {
            *num = *num * 10 + (c - '0');
            started = 1;
        } else {
            return 0;
        }
    }
}

int save_student_b(const char *filename, const struct student_t* s) {
    if (filename == NULL || s == NULL) return FILE_WRONG_INPUT;

    FILE* f = fopen(filename, "wb");
    if (!f) return FILE_CANNOT_OPEN_FILE;

    fwrite(s, sizeof(*s), 1, f);

    fclose(f);
    return FILE_OK;
}

int load_student_b(const char *filename, struct student_t* s) {
    if (filename == NULL || s == NULL) return FILE_WRONG_INPUT;

    FILE* f = fopen(filename, "rb");
    if (!f) return FILE_CANNOT_OPEN_FILE;

    if (!fread(s, sizeof(*s), 1, f)) {fclose(f); return FILE_FILE_CORRUPTED;}

    fclose(f);
    return FILE_OK;
}

int save_student_t(const char *filename, const struct student_t* s) {
    if (filename == NULL || s == NULL) return FILE_WRONG_INPUT;

    FILE* f = fopen(filename, "w");
    if (!f) return FILE_CANNOT_OPEN_FILE;

    fprintf(f, "%s, %s, %d, %s, %s, %d",
        s->name, s->surname, s->index, s->field, s->faculty, s->year);

    fclose(f);
    return FILE_OK;
}

int load_student_t(const char *filename, struct student_t* s) {
    if (filename == NULL || s == NULL) return FILE_WRONG_INPUT;

    FILE* f = fopen(filename, "r");
    if (!f) return FILE_CANNOT_OPEN_FILE;

    memset(s, 0, sizeof(*s));

    // read name
    int c;
    for (int i = 0; i < 19; i ++) {
        c = fgetc(f);
        if (c == ',') break;
        if (c == EOF) {fclose(f); return FILE_FILE_CORRUPTED;}
        *(s->name + i) = (char) c;
    }

    //get the space
    if (fgetc(f) != ' ') {fclose(f); return FILE_FILE_CORRUPTED;}
    for (int i = 0; i < 39; i ++) {
        c = fgetc(f);
        if (c == ',') break;
        if (c == EOF) {fclose(f); return FILE_FILE_CORRUPTED;}
        *(s->surname + i) = (char) c;
    }

    if (fgetc(f) != ' ') {fclose(f); return FILE_FILE_CORRUPTED;}
    if (!fscanf(f, "%d", &s->index)) {fclose(f); return FILE_FILE_CORRUPTED;}

    // get the comma and the space
    if (fgetc(f) != ',') {fclose(f); return FILE_FILE_CORRUPTED;}
    if (fgetc(f) != ' ') {fclose(f); return FILE_FILE_CORRUPTED;}

    for (int i = 0; i < 49; i ++) {
        c = fgetc(f);
        if (c == ',') break;
        if (c == EOF) {fclose(f); return FILE_FILE_CORRUPTED;}
        *(s->field + i) = (char) c;
    }

    // get the space
    if (fgetc(f) != ' ') {fclose(f); return FILE_FILE_CORRUPTED;}
    for (int i = 0; i < 79; i ++) {
        c = fgetc(f);
        if (c == ',') break;
        if (c == EOF) {fclose(f); return FILE_FILE_CORRUPTED;}
        *(s->faculty + i) = (char) c;
    }

    // get the space
    if (fgetc(f) != ' ') {fclose(f); return FILE_FILE_CORRUPTED;}
    if (!fscanf(f, "%d", &s->year)) {fclose(f); return FILE_FILE_CORRUPTED;}

    fclose(f);
    return FILE_OK;
}
