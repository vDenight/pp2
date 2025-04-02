#include <stdio.h>
#include <string.h>

struct file_t
{
    FILE *f;
    int size;
};

int open_file(struct file_t* f, const char *filename);
struct file_t* find_min(const struct file_t* files, int size);
void close_file(struct file_t* f);
_Bool read_line(char* buffer);
void append_to_file(struct file_t* file, char* buffer);

int main(void) {

    char buffer[1000];

    // file download phase

    printf("Podaj nazwy plikow:\n");

    struct file_t work_files[5];
    struct file_t* current_work_file = work_files;
    int work_files_count = 0;

    while(read_line(buffer)) {

        if(work_files_count >= 5) {
            continue;
        }

        if(!open_file(current_work_file, buffer)) {
            work_files_count++;
            current_work_file++;
        }
    }

    if(work_files_count == 0) {
        printf("Couldn't open file");
        return 4;
    }

    // text download phase

    printf("Podaj teksty:");

    while(read_line(buffer)) {

        struct file_t* file = find_min(work_files, work_files_count);

        append_to_file(file, buffer);

    }

    current_work_file = work_files;
    for(int i = 0; i < work_files_count; i++) {
        close_file(current_work_file);
        current_work_file++;
    }

    printf("Files saved");
    return 0;
}

void append_to_file(struct file_t* file, char* buffer) {

    FILE* fileHandle = file->f;
    char* currentPoint = buffer;

    for(size_t i = 0; i < strlen(buffer); i++) {
        fputc(*currentPoint, fileHandle);
        currentPoint++;
    }

    fputc('\n', fileHandle);

    file->size += strlen(buffer) + 1;
}

_Bool read_line(char* buffer) {

    int c;
    char* currentPoint = buffer;

    while((c = getchar()) != EOF && c != '\n') {
        *currentPoint = c;
        currentPoint++;
    }

    if(currentPoint == buffer)
        return 0;

    *currentPoint = '\0';
    return 1;
}

int open_file(struct file_t* f, const char *filename) {

    if (filename == NULL || f == NULL) {
        return 1;
    }

    FILE* file = fopen(filename, "a");

    if (file == NULL) {
        return 2;
    }

    // dante says the following line has no effect on the calculated size whatsoever
    // I guess this is the system dependent as on Windows I get size 0 but whatever
   // fseek(file, 0, SEEK_END);

    f->f = file;
    f->size = ftell(file);

    return 0;
}

struct file_t* find_min(const struct file_t* files, int size) {
    if (files == NULL || size <= 0) {
        return NULL;
    }

    struct file_t* min = (struct file_t*) files;
    struct file_t* current = (struct file_t*) files;

    for (int i = 0; i < size; i++) {
        if (min->size > current->size) {
            min = current;
        }
        current++;
    }

    return min;
}

void close_file(struct file_t* f) {
    if(f != NULL)
        if(f->f != NULL)
            fclose(f->f);
}