#include <stdio.h>

void readFilename(char* input);
int sumFromFile(FILE* file, _Bool* error);

int main(void) {
    printf("Podaj sciezke do pliku:\n");

    char input[31];
    _Bool error = 0;

    readFilename(input);

    FILE* f = fopen(input, "r");

    if (f == NULL) {
        printf("Couldn't open file");
        return 4;
    }

    int sum = sumFromFile(f, &error);

    if (error) {
        printf("file corrupted");
        fclose(f);
        return 6;
    }

    fclose(f);

    printf("Suma wczytanych liczb wynosi: %d", sum);
    return 0;

}

void readFilename(char* input) {
    int count = 0;
    char c;
    char* pointer = input;

    while ((c = getchar()) != '\n' && count < 30) {
        *pointer = c;
        pointer++;
        count++;
    }

    *pointer = '\0';
}

int sumFromFile(FILE* file, _Bool* error) {

    int sum = 0;
    int currentValue = 0;
    int scanfValue;

    while ((scanfValue = fscanf(file, "%d", &currentValue)) != EOF) {
        sum += currentValue;

        if (scanfValue == 0) {
            *error = 1;
            return 0;
        }
    }
    return sum;
}
