#include <stdio.h>
#include "input_output.h"

int main(void) {
    my_printf("Ala ma %d jablek ale %s ma %f w punkcie %p.", 1525091881, "Jacek", -13.9,
        (struct point_t) {13, 98});
    return 0;
}