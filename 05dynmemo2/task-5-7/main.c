#include <stdio.h>
#include "image_utils.h"

int main(void) {

    int err_code;
    struct image_t* image = load_image_t("test.txt", &err_code);
    printf("%d\n", err_code);

    return 0;
}