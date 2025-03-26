#include <stdio.h>

void addToFile(int liczba, int dzielnik, FILE* file);
void addToFile0(int liczba, FILE* file);

int main(void) {

    FILE* file2 = NULL;
    FILE* file3 = NULL;
    FILE* file5 = NULL;
    FILE* file0 = NULL;

    file2 = fopen("2.txt", "w");
    file3 = fopen("3.txt", "w");
    file5 = fopen("5.txt", "w");
    file0 = fopen("0.txt", "w");

    if (file2 == NULL || file3 == NULL || file5 == NULL || file0 == NULL) {
        printf("Couldn't create file");
        if (file2 != NULL) fclose(file2);
        if (file3 != NULL) fclose(file3);
        if (file5 != NULL) fclose(file5);
        if (file0 != NULL) fclose(file0);
        return 5;
    }

    printf("Podaj liczby:\n");

    int liczba = 0;

    fscanf(stdin, "%d", &liczba);

    while (liczba != 0) {
        addToFile(liczba, 2, file2);
        addToFile(liczba, 3, file3);
        addToFile(liczba, 5, file5);
        addToFile0(liczba, file0);
        fscanf(stdin, "%d", &liczba);
    }

    fclose(file2);
    fclose(file3);
    fclose(file5);
    fclose(file0);

    printf("Files saved");
    return 0;

}

void addToFile(int liczba, int dzielnik, FILE* file) {
    if (liczba % dzielnik == 0) {
        fprintf(file, "%d\n", liczba);
    }
}

void addToFile0(int liczba, FILE* file) {
    if ((liczba % 2 != 0) && (liczba % 3 != 0) && (liczba % 5 != 0)) {
        fprintf(file, "%d\n", liczba);
    }
}
