//
// Created by mrybczynski on 4/24/2025.
//

#include "image_utils.h"

#include <stdio.h>

struct image_t* load_image_t(const char *filename, int *err_code) {

    // wrong filename
    if (filename == NULL) {
        if (err_code)
            *err_code = 1;
        return NULL;
    }

    // open the file
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        if (err_code)
            *err_code = 2;
        return NULL;
    }

    // create the struct to load data into
    struct image_t *m1 = NULL;
    m1 = malloc(sizeof(struct image_t));

    if (m1 == NULL) {
        if (err_code)
            *err_code = 4;
        fclose(f);
        return NULL;
    }

    // data download phase
    fgets(m1->type, sizeof(m1->type), f); // gets two first letters

    // check with the getchar gets newline if not abort also check if type is P2
    if (fgetc(f) != '\n' ||
        *(m1->type) != 'P' || *(m1->type + 1)  != '2' || *(m1->type + 2)  != '\0')
        goto format_error;

    // now load the width and height
    int scanf_val = fscanf(f, "%d %d", &m1->width, &m1->height);
    if (scanf_val != 2 || m1->width <= 0 || m1->height <= 0)
        goto format_error;

    // now load the pixel max val
    int max_val;
    scanf_val = fscanf(f, "%d", &max_val);
    if (scanf_val != 1 || max_val <= 0)
        goto format_error;

    // now alloc the 2D array
    m1->ptr = malloc(m1->height * sizeof(int*));
    if (m1->ptr == NULL) {
        if (err_code)
            *err_code = 4;
        fclose(f);
        free(m1);
        return NULL;
    }

    // now each row
    for (int i = 0; i < m1->height; i++) {
        *(m1->ptr + i) = malloc(m1->width * sizeof(int));
        // advanced error handling xd
        if (*(m1->ptr + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(m1->ptr + j)); // free the allocated 1D int arrays
            }
            if (err_code)
                *err_code = 4;
            fclose(f);
            free(m1->ptr);
            free(m1);
            return NULL;
        }
    }

    // now we have allocated everything lets start inputing the data
    for (int i = 0; i < m1->height; i++) {
        for (int j = 0; j < m1->width; j++) {
            scanf_val = fscanf(f, "%d", *(m1->ptr + i) + j); // i hope this works
            if (scanf_val != 1 || *(*(m1->ptr + i) + j) > max_val || *(*(m1->ptr + i) + j) < 0) {
                for (int k = 0; k < m1->height; k++) {
                    free(*(m1->ptr + k));
                }
                if (err_code)
                    *err_code = 4;
                fclose(f);
                free(m1->ptr);
                free(m1);
                return NULL;
            }
        }
    }

    fclose(f);

    if (err_code)
        *err_code = 0;

    return m1;

format_error:
    if (err_code)
        *err_code = 3;
    fclose(f);
    free(m1);
    return NULL;
}

int save_image_t(const char * filename, const struct image_t *m1) {

    if (filename == NULL || m1 == NULL) {
        return 1;
    }

    FILE *f = fopen(filename, "w");

    if (f == NULL)
        return 2;




    fclose(f);
    return 0;


}
