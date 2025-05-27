#include <stdio.h>
#include "student_util.h"

int main(void) {
    printf("Podaj dane: \n");

    struct student_t student;
    struct student_t me;

    set(&me, "Michal", "Rybczynski",
        250269, "Computer Science", "IFE/WEEIA", 2025, NULL);

    int err;
    if (read(&student, &err)) {
        display(&student);
    } else {
        printf("Incorrect input\n");
    }

    display(&me);

    if (!err) {
        display_name(&student);
        display_surname(&student);
        display_index(&student);
        display_field(&student);
        display_faculty(&student);
        display_year(&student);
    }

    return err;
}