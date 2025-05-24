#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

enum main_code {
    ALLOC_FAIL = 8,
    FILE_CORRUPTED = 6,
    FILE_OPEN_FAIL = 4,
    INCORRECT_INPUT_DATA = 2,
    INCORRECT_INPUT = 1,
    OK = 0
};

_Bool get_word(FILE* file, char* buffer);
char* get_filename_a(char* filename);
char* get_filename_o(char* filename);

int main(void) {
    char* buffer = calloc(50, sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Podaj nazwe pliku: ");
    scanf("%49s", buffer);

    int opt = 0, scanf_val = 0;
    printf("Co chcesz teraz zrobic: ");
    scanf_val = scanf("%d", &opt);
    if (scanf_val != 1) {
        printf("Incorrect input");
        free(buffer);
        return INCORRECT_INPUT;
    }

    struct dictionary_t* my_dict;
    int err;

    char* filename_a = get_filename_a(buffer);
    char* filename_o = get_filename_o(buffer);
    if (filename_a == NULL || filename_o == NULL) {
        if (filename_a) free(filename_a);
        if (filename_o) free(filename_o);
        free(buffer);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    FILE* file = NULL;

    switch (opt) {
        case 0:
            my_dict = load_dictionary_b(buffer, &err);
            free(buffer);
            switch (err) {
                case LOAD_OK: break;

                case LOAD_ALLOC_FAIL:
                    free(filename_a);
                    free(filename_o);
                    printf("Failed to allocate memory");
                    return ALLOC_FAIL;

                case LOAD_FILE_OPEN_FAIL:
                    free(filename_a);
                    free(filename_o);
                    printf("Couldn't open file");
                    return FILE_OPEN_FAIL;

                case LOAD_FILE_CORRUPT:
                    free(filename_a);
                    free(filename_o);
                    printf("File corrupted");
                    return FILE_CORRUPTED;
                default: dictionary_display(my_dict); break;
            }
            break;
        case 1:

            file = fopen(buffer, "r");
            if (file == NULL) {
                printf("Couldn't open file");
                free(buffer);
                free(filename_a);
                free(filename_o);
                return FILE_OPEN_FAIL;
            }

            my_dict = create_dictionary(10, &err);

            if (err == CREATE_ALLOC_FAIL) {
                printf("Failed to allocate memory");
                free(buffer);
                free(filename_a);
                free(filename_o);
                fclose(file);
                return ALLOC_FAIL;
            }

            while (get_word(file, buffer)) {
                err = dictionary_add_word(my_dict, buffer);
                if (err == ADD_ALLOC_FAIL) {
                    printf("Failed to allocate memory");
                    free(buffer);
                    free(filename_a);
                    free(filename_o);
                    destroy_dictionary(&my_dict);
                    fclose(file);
                    return ALLOC_FAIL;
                }
            }
            free(buffer);
            fclose(file);
            break;
        default:
            printf("Incorrect input data");
            free(buffer);
            free(filename_a);
            free(filename_o);
            return INCORRECT_INPUT_DATA;
    }

    // now let's save the files
    dictionary_sort_occurence(my_dict);
    err = save_dictionary_b(my_dict, filename_o);
    if (err == SAVE_FILE_OPEN_FAIL) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }

    dictionary_sort_alphabetically(my_dict);
    err = save_dictionary_b(my_dict, filename_a);
    if (err == SAVE_FILE_OPEN_FAIL) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }

    destroy_dictionary(&my_dict);
    free(filename_a);
    free(filename_o);
    return OK;
}

char* get_filename_a(char* filename) {
    char* filename_a = calloc(strlen(filename) + 1 + strlen("_alpha"), sizeof(char));
    if (filename_a == NULL) {
        return NULL;
    }
    char* dot = strrchr(filename, '.');
    if (dot == NULL) {
        strcat(filename_a, "_alpha");
        return filename_a;
    }

    memcpy(filename_a, filename, strlen(filename) - strlen(dot));
    strcat(filename_a, "_alpha");
    strcat(filename_a, dot);
    return filename_a;
}

char* get_filename_o(char* filename) {
    char* filename_o = calloc(strlen(filename) + 1 + strlen("_occ"), sizeof(char));
    if (filename_o == NULL) {
        return NULL;
    }
    char* dot = strrchr(filename, '.');
    if (dot == NULL) {
        strcat(filename_o, "_occ");
        return filename_o;
    }

    memcpy(filename_o, filename, strlen(filename) - strlen(dot));
    strcat(filename_o, "_occ");
    strcat(filename_o, dot);
    return filename_o;
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
