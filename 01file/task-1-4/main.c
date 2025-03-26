#include <stdio.h>

void readFilename(char* input);
void revertTextFile(FILE* inputFile, FILE* outputFile);

int main(void) {

    FILE* inputFile = NULL;
    FILE* outputFile = NULL;

    char input[31];

    printf("Podaj sciezke do pliku:\n");
    readFilename(input);

    inputFile = fopen(input, "r");

    if (inputFile == NULL) {
        printf("Couldn't open file");
        return 4;
    }

    printf("Podaj sciezke do pliku wyjsciowego:\n");

    readFilename(input);

    outputFile = fopen(input, "w");

    if (outputFile == NULL) {
        fclose(inputFile);
        printf("Couldn't create file");
        return 5;
    }

    revertTextFile(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    printf("File copied");
    return 0;

}

void readFilename(char* input) {
    int count = 0;
    int c;
    char* pointer = input;

    while ((c = getchar()) != '\n') {
        if (count < 30) {
            *pointer = c;
            pointer++;
        }
        count++;
    }

    *pointer = '\0';
}

void revertTextFile(FILE* inputFile, FILE* outputFile) {

    fseek(inputFile, 0, SEEK_END);
    int fileSize = ftell(inputFile);

    if (fileSize == 0) {
        return;
    }

    for (int i = fileSize - 1; i >= 0; i-- ) {
        fseek(inputFile, i, SEEK_SET);
        fputc(fgetc(inputFile), outputFile);
    }
}
