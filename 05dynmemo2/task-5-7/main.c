#include <stdio.h>
#include <string.h>

#include "image_utils.h"

enum ERROR_CODES {
    FILE_OPEN_ERROR = 2,
    FILE_CORRUPTED_ERROR = 3,
    ALLOCATION_ERROR = 4,
};

char* create_modified_filename(const char* og_filename);

int main(void) {

    char* dest = NULL; // table of char for destination image filename
    struct image_t* dest_img = NULL; // destination image struct
    char* src_filename = NULL; // table of chars used for drawing additional images


    dest = (char*) malloc(40 * sizeof(char));
    if (dest == NULL)
        goto alloc_fail;

    printf("Enter destination image file name: ");
    scanf("%s", dest);

    int err_code;
    dest_img = load_image_t(dest, &err_code);

    switch (err_code) {
        case FILE_OPEN_ERROR:
            free(dest);
            printf("Couldn't open file");
            return 4;
        case FILE_CORRUPTED_ERROR:
            free(dest);
            printf("File corrupted");
            return 6;
        case ALLOCATION_ERROR:
            free(dest);
            goto alloc_fail;
        default: ;
    }

    printf("How many subimages you want to draw: ");
    int amount = 0;
    if (scanf("%d", &amount) != 1) {
        free(dest);
        destroy_image(&dest_img);
        printf("Incorrect input");
        return 1;
    }

    if (amount <= 0) {
        free(dest);
        destroy_image(&dest_img);
        printf("Incorrect input data");
        return 2;
    }

    src_filename = (char*) malloc(40 * sizeof(char));

    if (src_filename == NULL) {
        free(dest);
        destroy_image(&dest_img);
        goto alloc_fail;
    }

    struct image_t** srcs = NULL;

    srcs = calloc(sizeof(struct image_t *), amount);
    if (srcs == NULL) {
        free(src_filename);
        free(dest);
        destroy_image(&dest_img);
        goto alloc_fail;
    }

    int x = 0, y = 0;

    // now we take all the filenames separately
    for (int i = 0; i < amount; i++) {

        // filename
        printf("Enter a name of a subimage: ");
        scanf("%s", src_filename);
        *(srcs + i) = load_image_t(src_filename, &err_code);

        // error handling
        switch (err_code) {
            case FILE_OPEN_ERROR:
                printf("Couldn't open file\n");
                continue;
            case FILE_CORRUPTED_ERROR:
                printf("File corrupted\n");
                continue;
            case ALLOCATION_ERROR:
                for (int j = 0; j < i; j++) {
                    destroy_image(srcs + j);
                }
                free(src_filename);
                free(dest);
                free(srcs);
                destroy_image(&dest_img);
                goto alloc_fail;
            default: ;
        }

        //coping images
        printf("Enter coordinates (x, y): ");
        if (scanf("%d %d", &x, &y) != 2) {
            destroy_image(srcs + i);
            printf("Incorrect input");
            continue;
        }

        if (draw_image(dest_img, *(srcs + i), x, y)) {
            destroy_image(srcs + i);
            printf("Incorrect input");
        }
    }

    char* md_filename = create_modified_filename(dest);

    if (save_image_t(md_filename, dest_img)) {
        printf("Couldn't create file");

        for (int j = 0; j < amount; j++) {
            if (*(srcs + j) != NULL)
                destroy_image(srcs + j);
        }
        free(src_filename);
        free(srcs);
        free(dest);
        destroy_image(&dest_img);
        free(md_filename);
        return 5;

    }

    printf("File saved"); // success at last

    // cleaning
    for (int j = 0; j < amount; j++) {
        if (*(srcs + j) != NULL)
            destroy_image(srcs + j);
    }
    free(src_filename);
    free(srcs);
    free(dest);
    free(md_filename);
    destroy_image(&dest_img);
    return 0;

alloc_fail:
    printf("Failed to allocate memory");
    return 8;
}

char* create_modified_filename(const char* og_filename) {
    if (og_filename == NULL) {
        return NULL;
    }

    size_t og_len = strlen(og_filename);
    size_t md_len = og_len + strlen("_modified");
    char* md_filename = (char*) malloc((md_len + 1) * sizeof(char));
    if (md_filename == NULL) {
        return NULL;
    }

    strcpy(md_filename, og_filename);
    strcat(md_filename, "_modified");

    return md_filename;
}