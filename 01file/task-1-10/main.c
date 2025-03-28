#include <stdio.h>

void readFilename(char* input);
void readSecretMessage(FILE* cordHandle, FILE* messageHandle);

int main(void) {
    printf("Podaj sciezke do pliku:\n");

    char input[31];

    readFilename(input);

    FILE* cordHandle = fopen(input, "r");

    if (cordHandle == NULL) {
        printf("Couldn't open file");
        return 4;
    }

    FILE* messageHandle = fopen(input, "r");

    if (messageHandle == NULL) {
        printf("Couldn't open file");
        fclose(cordHandle);
        return 4;
    }

    readSecretMessage(cordHandle, messageHandle);

    fclose(cordHandle);
    fclose(messageHandle);
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

void readSecretMessage(FILE* cordHandle, FILE* messageHandle) {

    long int coordinatePos = 0;
    long int messagePos = 0;
    long int endPos = 0;

    int c = 0;

    do {
        c = getc(messageHandle);
        messagePos++;
    } while (c != '\n' && c != EOF);

    // you can check if it has encountered EOF and error handle, or maybe its better to just use ftell and then check if eof is next of smth

    fseek(messageHandle, 0, SEEK_END);
    endPos = ftell(messageHandle);

    // now we have all the positions lets start some work


    int characterIndex = 0;

    while (ftell(cordHandle) != messagePos - 1) {
        fscanf(cordHandle, "%d", &characterIndex);
        printf("read number: %d ", characterIndex);

        if (characterIndex > endPos || characterIndex < messagePos) {
            printf("Wrong input\n");
            return;
        }

        fseek(messageHandle, characterIndex + 11, SEEK_SET);
        printf("file position: %d ", ftell(messageHandle));
        printf("read character: %c\n", fgetc(messageHandle));
    }

}
