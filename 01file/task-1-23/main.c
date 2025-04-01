#include <stdio.h>

void readFilename(char* input);
int read_file(const char* filename);
void process_buffer(char* input);
void print_file(FILE* file);

int main(void) {
    printf("Podaj sciezke do pliku:\n");

    char input[31];

    readFilename(input);

    // check if file exists
    FILE* file = fopen(input, "r");
    if (file == NULL) {
        printf("couldn't open file");
        return 4;
    }
    fclose(file);

    int count = read_file(input);
    printf("%d", count);

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

    if (filename == NULL) {
        return -1;
    }

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    int count = 0;

    char buffer[31];
    while (fgets(buffer, 30, file) != NULL) {
        process_buffer(buffer);
        printf("%s\n", buffer);
        count += read_file(buffer);
    }

    fclose(file);
    return count + 1;
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

