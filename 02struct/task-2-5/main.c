#include <stdio.h>
#include <string.h>

#include "student_util.h"

enum file_format {
    BINARY,
    TEXT,
    UNSUPPORTED
};

enum main_code {
    OK = 0,
    UNSUPPORTED_FILE_FORMAT = 7,
    COULD_NOT_CREATE_FILE = 5,
    FILE_CORRUPTED = 6,
    CANNOT_OPEN_FILE = 4
};

enum file_format read_format(char* filename);

int main(void) {
    printf("Podaj dane: \n");

    struct student_t student;
    char filename[100] = {0};

    int err;
    if (read(&student, &err)) {
        display(&student);
    } else {
        printf("Incorrect input\n");
    }

    printf("Enter file name:\n");
    scanf("%99s", filename);
    int save_val;
    enum file_format file_format = read_format(filename);
    switch (file_format) {
        case BINARY:
            save_val = save_student_b(filename, &student);
            break;
        case TEXT:
            save_val = save_student_t(filename, &student);
            break;
        case UNSUPPORTED:
            printf("Unsupported file format");
            return UNSUPPORTED_FILE_FORMAT;
    }

    return err;
}

enum file_format read_format(char* filename) {
    if (filename == NULL) return UNSUPPORTED;

    char* dot = strrchr(filename, '.');
    if (dot == NULL) return UNSUPPORTED;
    if (strcmp(dot + 1, "bin") == 0) return BINARY;
    if (strcmp(dot + 1, "txt") == 0) return TEXT;
    return UNSUPPORTED;
}