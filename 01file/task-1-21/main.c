#include <stdio.h>

void readFilename(char* input);
_Bool readSecretMessage(FILE* cordHandle, FILE* messageHandle);
_Bool verifyCoords(FILE* cordHandle, long int messagePos, long int endPos);

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

    if (!readSecretMessage(cordHandle, messageHandle)) {
        printf("file corrupted");
        fclose(cordHandle);
        fclose(messageHandle);
        return 6;
    }

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

_Bool readSecretMessage(FILE* cordHandle, FILE* messageHandle) {

    long int messagePos = 0;
    long int endPos = 0;

    int c = 0;

    do {
        c = getc(messageHandle);
        messagePos++;
    } while (c != '\n' && c != EOF);

    if (c == EOF || messagePos == 1) {
        return 0;
    }

    fseek(messageHandle, 0, SEEK_END);
    endPos = ftell(messageHandle);

    if (!verifyCoords(cordHandle, messagePos, endPos)) {
        return 0;
    }

    long int characterIndex = 0;
    while (ftell(cordHandle) != messagePos - 1) {
        fscanf(cordHandle, "%ld", &characterIndex);
        fseek(messageHandle, characterIndex, SEEK_SET);
        printf("%c", fgetc(messageHandle));
    }

    return 1;

}

_Bool verifyCoords(FILE* cordHandle, long int messagePos, long int endPos) {

    long int currentPos = ftell(cordHandle);
    fseek(cordHandle, 0, SEEK_SET);

    long int characterIndex = 0;

    while (ftell(cordHandle) != messagePos - 1) {
        int scanfVal = fscanf(cordHandle, "%ld", &characterIndex);

        if (characterIndex >= endPos || characterIndex < messagePos || scanfVal == 0) {
            return 0;
        }
    }

    fseek(cordHandle, currentPos, SEEK_SET);
    return 1;
}
