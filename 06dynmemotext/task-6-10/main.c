#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum main_code {
    OK = 0,
    ALLOC_FAIL = 8
};

int main(void) {
    int current_capacity = 50; // actually it is 49 :)
    int current_size = 0;
    char* buffer = realloc(NULL, 50);
    if (!buffer) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }
    memset(buffer, 0, 50);

    printf("Podaj tekst: ");

    int c;
    while (1) {
        c = getchar();
        if (c == '\n') break;

        if (current_size == current_capacity - 1) {
            char* temp = realloc(buffer, current_capacity + 50);
            if (!temp) {
                break;
            }
            memset(temp + current_capacity, 0, 50);
            current_capacity += 50;
            buffer = temp;
        }

        *(buffer + current_size) = (char) c;
        current_size++;
    }

    printf("%s", buffer);
    free(buffer);
    return OK;
}