#include <stdio.h>

void readFilename(char* input);
int file_size_from_path(const char *path);
int file_size_from_file(FILE *f);

int main(void) {
    printf("Podaj sciezke do pliku:\n");

    char input[31];

    readFilename(input);

    int size1 = file_size_from_path(input);

    FILE* f = fopen(input, "r");
    int size2 = file_size_from_file(f);
    if (f != NULL)
        fclose(f);

    if (size1 != size2 || size1 < 0) {
        printf("Couldn't open file");
        return 4;
    }

    printf("Rozmiar pliku wynosi %d bajtow\n", size1);
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

int file_size_from_path(const char *path) {

    if (!path)
        return -2;

    FILE* f = fopen(path, "r");

    if (f == NULL)
        return -1;

    int size = file_size_from_file(f);
    fclose(f);

    return size;

}

int file_size_from_file(FILE *f) {

    if (f == NULL)
        return -2;

    int size = 0;
    long int currentPos = ftell(f);

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, currentPos, SEEK_SET);

    return size;
}
