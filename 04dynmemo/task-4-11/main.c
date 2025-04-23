#include <ctype.h>
#include <stdio.h>
#include "vector.h"

enum OPTION {
    EXIT = 0,
    ADD,
    DELETE
};

void display(struct vector_t* vec);

int main(void) {
    printf("Podaj pojemność tablicy: ");
    int capacity;

    if (scanf("%d", &capacity) != 1) {
        goto incorrect_input;
    }

    if (capacity <= 0) {
        goto incorrect_input_data;
    }

    struct vector_t* my_vector;
    if (vector_create_struct(&my_vector, capacity)) {
        goto alloc_fail;
    }

    int option;
    int read_value;
    int push_back_val;

    while (1) {
        printf("Co chcesz zrobic: ");
        if (scanf("%d", &option) != 1) {
            vector_destroy_struct(&my_vector);
            goto incorrect_input;
        }

        switch (option) {
            case EXIT:
                vector_destroy_struct(&my_vector);
                return 0;
            case ADD:
                printf("Podaj kolejne liczby, które mają zostać dodane do tablicy: ");
                while (1) {
                    if (scanf("%d", &read_value) != 1) {
                        vector_destroy_struct(&my_vector);
                        goto incorrect_input;
                    }
                    if (read_value == 0)
                        break;
                    push_back_val = vector_push_back(my_vector, read_value);
                    if (push_back_val == 2) {
                        printf("Failed to allocate memory\n");
                        break;
                    }
                }
                display(my_vector);
                break;
            case DELETE:
                printf("Podaj kolejne liczby, które mają zostać usuniete z tablicy: ");
                while (1) {
                    if (scanf("%d", &read_value) != 1) {
                        vector_destroy_struct(&my_vector);
                        goto incorrect_input;
                    }
                    if (read_value == 0)
                        break;
                    vector_erase(my_vector, read_value);
                }
                display(my_vector);
                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    }

incorrect_input:
    printf("Incorrect input");
    return 1;

incorrect_input_data:
    printf("Incorrect input data");
    return 2;

alloc_fail:
    printf("Failed to allocate memory");
    return 8;
}

void display(struct vector_t* vec) {
    if (vec->size == 0) {
        printf("Buffer is empty\n");
        return;
    }
    vector_display(vec);
}