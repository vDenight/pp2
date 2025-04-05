#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct message_t
{
    char a; // 1 byte
    double b; // 8 bytes
    int c; // 4 bytes
};

int load_data(struct message_t *cp, int size, const char *filename);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);

int main(void) {

    struct message_t message_array[100];

    char msg[1000];

    load_data(message_array, 10, "test2.bin");

    decode_message(message_array, 10, msg, 110);

    printf("secret: %s\n", msg);

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
    fread(&amount_of_bytes, sizeof(unsigned int), 1, fp);

    if (amount_of_bytes  % 24 != 0)
        return -3;

    int read_amount = (int) fread(cp, sizeof(struct message_t), size, fp);
    if (read_amount  * 24 != amount_of_bytes)
        return -3;

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
        for (int j = 0; j < sizeof(struct message_t); j++) {
            if ((void*) current_point >= int_pointer && (void*) current_point < int_pointer + sizeof(int)) {
                current_point ++;
                continue;
            }

            if ((void*) current_point >= double_pointer && (void*) current_point < double_pointer + sizeof(double)) {
                current_point ++;
                continue;
            }

            if ((void*) current_point == char_pointer) {
                current_point ++;
                continue;
            }
            *msg = *current_point;
            msg++;
            current_text_size ++;
            current_point ++;
        }

        current_message_pointer ++;
    }

    return 0;
}