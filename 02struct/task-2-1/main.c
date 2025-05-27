#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include <time.h>

int main(void) {

    struct point_t user_point = {0};
    struct point_t random_point = {0};

    if (!read(&user_point)) {
        printf("Incorrect input");
        return 1;
    }

    srand(time(NULL));
    set(&random_point, rand() % 200 - 100, rand() % 200 - 100);

    // now printing
    show(&user_point);
    show(&random_point);
    printf("%.2f", distance(&user_point, &random_point, NULL));

    return 0;
}