#include <stdio.h>
#include "student_util.h"

int main(void) {
    printf("Podaj dane: \n");

    struct student_t student;
    int err;
    if (read(&student, &err)) {
        show(&student);
    } else {
        printf("Incorrect input");
        return err;
    }

    return 0;
}