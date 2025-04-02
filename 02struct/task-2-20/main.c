#include <stdio.h>

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename);

int main(void) {

    struct message_t message_array[100];

    load_data(message_array, 2, "2420test1.bin");
    printf("%c\n", message_array[0].a);
    printf("%f\n", message_array[0].b);
    printf("%d\n", message_array[0].c);



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

    fread(cp, sizeof(struct message_t), size, fp);

    return 0;
}