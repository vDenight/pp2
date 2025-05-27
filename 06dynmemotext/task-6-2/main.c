#include <stdio.h>
#include "student_util.h"

int main(void) {

    int err;
    struct student_t* student = read(&err);

    if (!err) {
        show(student);
    } else if (err == READ_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return 8;
    } else {
        printf("Incorrect input");
        return err;
    }

    destroy(&student);
    return 0;
}