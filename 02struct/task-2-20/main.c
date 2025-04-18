#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct message_t
{
    char a; // 1 byte
    double b; // 8 bytes
    int c; // 4 bytes
};

int load_data(struct message_t *cp, int size, const char *filename);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);
void readFilename(char* input);

int main(void) {

    struct message_t message_array[100];
    char msg[1101];
    char input[31];

    printf("Enter filename: ");
    readFilename(input);

    int loaded_amount = load_data(message_array, 100, input);

    if (loaded_amount == -2) {
        printf("Couldn't open file");
        return 4;
    }

    if (loaded_amount == -3) {
        printf("File corrupted");
        return 6;
    }

    decode_message(message_array, loaded_amount, msg, 1101);

    printf("%s", msg);

    return 0;
}

int load_data(struct message_t *cp, int size, const char *filename) {

    if (cp == NULL || filename == NULL || size <= 0) {
        return -1;
    }

    FILE *fp = NULL;
    fp = fopen(filename, "rb");

    if (fp == NULL)
        return -2;

    unsigned int amount_of_bytes = 0;
    size_t fread_value = fread(&amount_of_bytes, sizeof(unsigned int), 1, fp);
    if (fread_value != 1) {
        fclose(fp);
        return -3;
    }

    if (amount_of_bytes  % 24 != 0) {
        fclose(fp);
        return -3;
    }

    int read_amount = (int) fread(cp, sizeof(struct message_t), size, fp);

    // if (read_amount  * 24 != amount_of_bytes)
    //     return -3;

    fclose(fp);

    return read_amount;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size) {

    if (cp == NULL || msg == NULL || text_size <= 0 || size <= 0) {
        return 1;
    }

    struct message_t* current_message_pointer = (struct message_t*) cp;
    char* current_point = (char*) cp;
    int current_text_size = 0;

    for (int i = 0; i < size; i++) {

        void *double_pointer = &current_message_pointer->b;
        void *char_pointer = &current_message_pointer->a;
        void *int_pointer = &current_message_pointer->c;

        while (current_point < (char*) current_message_pointer + 24) {

            if (current_text_size == text_size - 1) {
                *msg = '\0';
                return 0;
            }

            if ((void*) current_point == int_pointer) {
                current_point += 4;
                continue;
            }

            if ((void*) current_point == double_pointer) {
                current_point += 8;
                continue;
            }

            if ((void*) current_point == char_pointer) {
                current_point ++;
                continue;
            }
            memcpy((char*) msg, (char*) current_point, 1);
            msg++;
            current_text_size ++;
            current_point ++;
        }

        current_message_pointer ++;
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

