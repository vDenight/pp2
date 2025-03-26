#include <stdio.h>

void readFilename(char* input);
void writeNumbers(FILE* file);

int main(void) {

    FILE* file = NULL;

    char input[31];

    printf("Podaj sciezke do pliku:\n");
    readFilename(input);

    file = fopen(input, "w");

    if (file == NULL) {
        printf("Couldn't create file");
        return 5;
    }

    writeNumbers(file);

    fclose(file);

    printf("File saved");
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

void writeNumbers(FILE* file) {

    for (int i = 0 ; i <= 100; i ++) {
        fprintf(file, "%d\n", i);
    }

}
