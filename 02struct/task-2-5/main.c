#include <ctype.h>
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
    INCORRECT_INPUT = 1,
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
        return err;
    }

    printf("Enter file name:\n");
    scanf("%99s", filename);
    int file_function_val = {0};
    int file_format = read_format(filename);
    switch (file_format) {
        case BINARY:
            file_function_val = save_student_b(filename, &student);
            break;
        case TEXT:
            file_function_val = save_student_t(filename, &student);
            break;
        case UNSUPPORTED:
            printf("Unsupported file format");
            return UNSUPPORTED_FILE_FORMAT;
        default: return 2137;
    }

    switch (file_function_val) {
        case FILE_OK:
            printf("File saved\n");
            break;
        case FILE_CANNOT_OPEN_FILE:
            printf("Couldn't create file\n");
            return COULD_NOT_CREATE_FILE;
        default:
            display_name(&student);
            display_surname(&student);
            display_index(&student);
            display_field(&student);
            display_faculty(&student);
            display_year(&student);
            set(&student, "nie", "nawidze", 2137, "dante", "serio", 1337, NULL);
        break;
    }

    printf("Do you want to read the file (Y/N)? ");
    getchar(); // get the newline first
    char c;
    scanf("%c", &c);
    
    if (toupper(c) == 'N') return OK;
    if (toupper(c) == 'Y') {
        switch (file_format) {
            case BINARY:
                file_function_val = load_student_b(filename, &student);
            break;
            case TEXT:
                file_function_val = load_student_t(filename, &student);
            break;
        }

        switch (file_function_val) {
            case FILE_OK:
                display(&student);
                return OK;
            case FILE_CANNOT_OPEN_FILE:
                printf("Couldn't open file");
                return CANNOT_OPEN_FILE;
            case FILE_FILE_CORRUPTED:
                printf("File corrupted");
                return FILE_CORRUPTED;
            default: return 2137;
        }
    }

    printf("Incorrect input");
    return INCORRECT_INPUT;
}

enum file_format read_format(char* filename) {
    if (filename == NULL) return UNSUPPORTED;

    char* dot = strrchr(filename, '.');
    if (dot == NULL) return UNSUPPORTED;
    if (strcmp(dot + 1, "bin") == 0) return BINARY;
    if (strcmp(dot + 1, "txt") == 0) return TEXT;
    return UNSUPPORTED;
}