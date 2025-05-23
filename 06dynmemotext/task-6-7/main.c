#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

enum main_code {
    ALLOC_FAIL = 8,
    FILE_OPEN_FAIL = 4,
    OK = 0
};

_Bool get_word(FILE* file, char* buffer);

int main(void) {

    char* buffer = calloc(50, sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Podaj nazwe pliku: ");
    scanf("%49s", buffer);

    FILE* file = fopen(buffer, "r");
    if (file == NULL) {
        printf("Couldn't open file");
        free(buffer);
        return FILE_OPEN_FAIL;
    }

    int err;
    struct dictionary_t* my_dict = create_dictionary(10, &err);

    if (err == CREATE_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        free(buffer);
        fclose(file);
        return ALLOC_FAIL;
    }

    _Bool is_empty = 1;

    while (get_word(file, buffer)) {
        is_empty = 0;
        err = dictionary_add_word(my_dict, buffer);
        if (err == ADD_ALLOC_FAIL) {
            printf("Failed to allocate memory");
            free(buffer);
            destroy_dictionary(&my_dict);
            fclose(file);
            return ALLOC_FAIL;
        }
    }

    if (is_empty) printf("Nothing to show");
    else dictionary_display(my_dict);

    fclose(file);
    destroy_dictionary(&my_dict);
    free(buffer);
    return OK;
}

_Bool get_word(FILE* file, char* buffer) {
    _Bool started = 0;
    int current_char;
    int index = 0;
    while (1) {

        if (index == 49) {
            *(buffer + index) = '\0';
            break;
        }

        current_char = fgetc(file);

        if (current_char == EOF && started == 0) return 0;

        if (isalpha(current_char)) {
            started = 1;
            *(buffer + index) =  (char) current_char;
            index++;
        } else {
            if (started == 1) {
                *(buffer + index) = '\0';
                break;
            }
        }
    }

    return 1;
}
