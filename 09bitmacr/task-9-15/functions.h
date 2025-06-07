//
// Created by mrybczynski on 6/6/2025.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

enum load_err {
    FILE_OPEN_ERROR = 2,
    FILE_CORRUPTED_ERROR = 3,
    ALLOC_ERROR = 4
};

#define DEFINE_ARRAY(TYPE) \
    struct array_##TYPE##_t { \
        int size; \
        int capacity; \
        TYPE *data; \
    }; \

#define CREATE_ARRAY(TYPE) \
    struct array_##TYPE##_t *create_array_##TYPE(int size) { \
        if (size < 1) return NULL; \
        struct array_##TYPE##_t* arr = calloc(1, sizeof(struct array_##TYPE##_t)); \
        if (!arr) return NULL; \
        arr->data = calloc(size, sizeof(TYPE)); \
        if (!arr->data) { free(arr); return NULL; } \
        \
        arr->size = 0; \
        arr->capacity = size; \
        \
        return arr; \
    } \

#define FREE_ARRAY(TYPE) \
    void free_array_##TYPE(struct array_##TYPE##_t *array) { \
        if (!array) return; \
        if (array->data) free(array->data); \
        free(array); \
    } \

#define SAVE_ARRAY(TYPE) \
    int save_array_##TYPE(const struct array_##TYPE##_t *array, const char *filename) { \
        if (!array || !array->data || !filename || array->size < 1 || array->capacity < 1 || array->size > array->capacity) return 1; \
        \
        FILE* f = fopen(filename, "wb"); \
        if (!f) return 2; \
        \
        fwrite(&(array->size), sizeof(int), 1, f); \
        fwrite(array->data, sizeof(TYPE), array->size, f); \
        \
        fclose(f); \
        return 0; \
    } \

#define LOAD_ARRAY(TYPE) \
    int load_array_##TYPE(struct array_##TYPE##_t **array, const char *filename) { \
        if (!array || !filename) return 1; \
        \
        FILE* f = fopen(filename, "rb"); \
        if (!f) return FILE_OPEN_ERROR; \
        \
        int cap = 0; \
        fread(&cap, sizeof(int), 1, f); \
        if (cap < 1) { fclose(f); return FILE_CORRUPTED_ERROR; } \
        \
        struct array_##TYPE##_t *arr = create_array_##TYPE(cap); \
        if (!arr) { fclose(f); return ALLOC_ERROR; } \
        \
        int fread_val = fread(arr->data, sizeof(TYPE), cap, f); \
        if (fread_val != cap) { fclose(f); free_array_##TYPE(arr); return FILE_CORRUPTED_ERROR; } \
        arr->size = cap; \
        \
        fclose(f); \
        \
        *array = arr; \
        return 0; \
    } \

#define SORT_ARRAY(TYPE) \
    int compare_##TYPE(const void* a, const void* b) { \
        if (*(TYPE*)a > *(TYPE*)b) return 1; \
        if (*(TYPE*)a < *(TYPE*)b) return -1; \
        return 0; \
    } \
    \
    int sort_array_##TYPE(struct array_##TYPE##_t *array) { \
        if (!array || !array->data || array->size < 1 || array->capacity < 1 || array->size > array->capacity) return 1; \
        qsort(array->data, array->size, sizeof(*(array->data)), compare_##TYPE); \
        return 0; \
    } \

#endif //FUNCTIONS_H
