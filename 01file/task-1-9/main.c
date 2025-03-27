#include <ctype.h>
#include <stdio.h>

void readFilename(char* input);
int readAmountFromFile(FILE* input);
int sumFromFileWithAmount(FILE* file, int amount, _Bool* error);

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

    int amount = readAmountFromFile(f);

    if (amount < 0) {
        printf("file corrupted");
        fclose(f);
        return 6;
    }

    int sum = sumFromFileWithAmount(f, amount, &error);

    if (error) {
        printf("file corrupted");
        fclose(f);
        return 6;
    }

    float average = (float) sum / amount;

    printf("%d\n", sum);
    printf("%f\n", average);

    fclose(f);
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

int readAmountFromFile(FILE* input) {

    int c;
    int value = 0;

    while ((c = getc(input)) != '\n') {
        if (!isdigit(c)) {
            return -1;
        }
        value = (value * 10) + (c - '0');
    }

    return value;

}

int sumFromFileWithAmount(FILE* file, int amount, _Bool* error) {

    int sum = 0;
    int currentValue = 0;

    for (int i = 0; i < amount; i++) {
        int scanfValue = fscanf(file, "%d", &currentValue);

        if (scanfValue == EOF || scanfValue == 0) {
            *error = 1;
            return 0;
        }

        sum += currentValue;
    }

    return sum;
}
