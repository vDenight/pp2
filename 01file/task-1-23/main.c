#include <stdio.h>
#include <string.h>

void readFilename(char* input);
int read_file(const char* filename);
void process_buffer(char* input);
void print_file(FILE* file);

int main(void) {
    printf("Podaj sciezke do pliku:\n");

    char input[31];

    readFilename(input);

    if (read_file(input) < 0) {
        printf("Couldn't open file");
        return 4;
    }

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

int read_file(const char* filename) {

    FILE* file = fopen(filename, "r");

    if (file == NULL)
        return -1;

    int count = 0;

    char buffer[31];

    while (fgets(buffer, 50, file) != NULL) {
        process_buffer(buffer);
        printf("%s\n", buffer);
        FILE* innerFile = fopen(buffer, "r");
        if (innerFile == NULL)
            continue;

        // the opening is successful
        count++;
        print_file(innerFile);
        fclose(innerFile);
    }

    fclose(file);

    return count;

}

void process_buffer(char* input) {

    char* pointer = input;
    int count = 0;

    while (count < 30) {
        if (*pointer == '\n' || *pointer == '\0') {
            *pointer = '\0';
            return;
        }
        pointer++;
        count++;
    }

    *pointer = '\0';
}

void print_file(FILE* file) {
    int c;

    while ((c = getc(file)) != EOF) {
        printf("%c", c);
    }

}

