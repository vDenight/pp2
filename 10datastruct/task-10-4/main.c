#include <stdio.h>
#include "stack.h"

enum main_code {
    OK = 0,
    CANNOT_CREATE_FILE = 5,
    ALLOC_FAIL = 8,
    NOT_ENOUGH_ARGS = 9
};

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Not enough arguments");
        return NOT_ENOUGH_ARGS;
    }

    for (int i = 1; i < argc; i++) {

        struct stack_t* sp = NULL;

        int err_code = stack_load(&sp, *(argv + i));
        if (err_code == STACK_CANNOT_OPEN_FILE) {
            printf("Couldn't open file %s\n", *(argv + i));
            continue;
        }
        if (err_code == STACK_LOAD_ALLOC_FAIL) {
            printf("Failed to allocate memory");
            return ALLOC_FAIL;
        }

        err_code = stack_save(sp, *(argv + i));
        if (err_code == STACK_CANNOT_OPEN_FILE) {
            stack_destroy(&sp);
            printf("Couldn't create file");
            return CANNOT_CREATE_FILE;
        }
        printf("File %s saved\n", *(argv + i));
        stack_destroy(&sp);
    }

    return OK;
}