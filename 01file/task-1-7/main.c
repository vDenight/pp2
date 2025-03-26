#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int readInt();
void createFileName(char* buffer, int index);
void addNumber(FILE* file, int number);

int main(void) {

    srand(time(NULL));
    printf("Podaj liczbe liczb:\n");
    int amount = readInt();

    if (amount == 0 || amount > 1000) {
        printf("Incorrect input data");
        return 2;
    }

    if (amount < 0) {
        printf("Incorrect input");
        return 1;
    }

    int numberOfFiles = amount % 10 == 0 ? amount / 10 : amount / 10 + 1;
    char fileName[10];

    for (int i = 0; i < numberOfFiles; i++) {
        createFileName(fileName, i);
        FILE* file = NULL;
        file = fopen(fileName, "w");

        if (file == NULL) {
            printf("Couldn't create file");
            return 5;
        }

        if (i == numberOfFiles - 1 && amount % 10 != 0) {
            for (int j = 0; j < amount % 10; j++) {
                addNumber(file, rand() % 1001);
            }
        } else {
            for (int j = 0; j < 10; j++) {
                addNumber(file, rand() % 1001);
            }
        }

        printf("%d.txt\n", i);
        fclose(file);
    }

    return 0;

}

int readInt() {

    int finalValue = 0;
    int c;
    _Bool first = 1;

    while ((c = getchar()) != '\n') {

        if (first && c == '-')
            return 0;

        first = 0;

        if (!isdigit(c))
            return -1;

        finalValue = finalValue * 10 + (c - '0');
    }

    return finalValue;
}

void createFileName(char* buffer, int index) {
    snprintf(buffer, 10, "%d.txt", index);
}

void addNumber(FILE* file, int number) {
    fprintf(file, "%d\n", number);
}
