#include <stdio.h>
#include <string.h>

#include "double_to_char.h"
#include "read_line.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    COULD_NOT_CREATE_FILE = 5,
    COULD_NOT_OPEN_FILE = 4,
    FILE_CORRUPTED = 6
};

int main(void) {

    double value = {0};

    printf("Podaj liczbe: ");
    int scnaf_val = scanf("%lf", &value);
    if (scnaf_val != 1) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    // after scanf we need to clear the buffer from the newline
    if (getchar() != '\n') {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    union double_to_char_t dtc;
    dtc.d = value;

    char buff[40] = {0};
    printf("Podaj nazwe pliku: ");
    read_line(buff, 39);

    int save_code = save_double(&dtc, buff);
    if (save_code == SAVE_CANNOT_OPEN_FILE) {
        printf("Couldn't create file");
        return COULD_NOT_CREATE_FILE;
    }

    printf("File saved\n");
    memset(buff, 0, sizeof(buff));
    printf("Podaj nazwe pliku: ");
    read_line(buff, 39);

    int load_code = load_double(&dtc, buff);

    if (load_code == LOAD_CANNOT_OPEN_FILE) {
        printf("Couldn't open file");
        return COULD_NOT_OPEN_FILE;
    }

    if (load_code == LOAD_FILE_CORRUPTED) {
        printf("File corrupted");
        return FILE_CORRUPTED;
    }

    printf("%lf", dtc.d);

}