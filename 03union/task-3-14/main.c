#include <stdio.h>
#include "mix_types.h"

int main() {

    printf("Enter elements (single characters, signed integers and doubles):\n");
    struct data_t my_data[100] = {0};
    struct data_t* my_data_point[100] = {0};
    int size = 0;

    int read_value = 0;

    int i;
    for (i = 0; i < 100; i++) {
        *(my_data_point + i) = &(*(my_data + i));
        read_value = read_mix_type(*(my_data_point + i));
        size++;
        if (read_value == READ_CORRUPTED_DATA) {
            printf("Incorrect input data");
            return 2;
        }
        if (read_value == READ_FINISHED) {
            break;
        }
    }
    sort(my_data_point, size);
    display(my_data_point, size);

    return 0;
}