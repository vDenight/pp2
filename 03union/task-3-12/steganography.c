//
// Created by mrybczynski on 5/5/2025.
//

#include <stdio.h>
#include "steganography.h"

#include <string.h>
/*
3 - jezeli niemozliwe bedzie zakodowania calej wiadomosci w pliku,
4 - jezeli nie uda sie utworzyc pliku wyjsciowego,
2 - jezeli plik wejsciowy nie bedzie istanial,
1 - w przypadku blednych danych przekazanych podczas wywolywania funkcji encode,
0 - w przypadku sukcesu.
*/
int encode(const char *input, char *txt, const char *output) {
    if (input == NULL || txt == NULL || output == NULL) {
        return 1;
    }

    FILE* input_file = fopen(input, "r");
    if (input_file == NULL) {
        return 2;
    }

    FILE* output_file = fopen(output, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return 4;
    }

    union pixel pixel = {0};
    union bit_character character = {0};
    int fscanf_val = 0;
    unsigned int read_val = 0;

    for (int i = 0; i < (int) strlen(txt); i++) {
        character.char_value = *(txt + i);
        for (int j = 0; j < 8; j++) {
            fscanf_val = fscanf(input_file, "%u", &read_val);
            if (fscanf_val == -1 || fscanf_val == 0) {
                // not whole message was encoded
                fclose(input_file);
                fclose(output_file);
                return 3;
            }

            pixel.pixel_value = read_val;

            switch (j) {
                case 0: pixel.least_significant = character.bits.b7; break;
                case 1: pixel.least_significant = character.bits.b6; break;
                case 2: pixel.least_significant = character.bits.b5; break;
                case 3: pixel.least_significant = character.bits.b4; break;
                case 4: pixel.least_significant = character.bits.b3; break;
                case 5: pixel.least_significant = character.bits.b2; break;
                case 6: pixel.least_significant = character.bits.b1; break;
                case 7: pixel.least_significant = character.bits.b0; break;
                default: break;
            }

            fprintf(output_file, "%u", pixel.pixel_value);

            // now to copy the whitespace (or new line)

            fputc(fgetc(input_file), output_file);
            char new_line = fgetc(input_file);
            if (new_line == '\n') {
                fputc(new_line, output_file);
            } else {
                fseek(input_file, -1, SEEK_CUR);
            }
            // done
        }
    }

    // now fill the rest of the bits with 0000 0000

    while (fscanf(input_file, "%u", &read_val) == 1) {
        pixel.pixel_value = read_val;
        pixel.least_significant = 0;
        fprintf(output_file, "%u", pixel.pixel_value);

        fputc(fgetc(input_file), output_file);
        char new_line = fgetc(input_file);
        if (new_line == '\n') {
            fputc(new_line, output_file);
        } else {
            fseek(input_file, -1, SEEK_CUR);
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

/*
3 - jezeli dane w pliku wejsciowym beda uszkodzone,
1 - w przypadku blednych danych wejsciowych,
2 - kiedy nie uda sie otworzyc pliku wejsciowego,
0 - w przypadku sukcesu.
*/
int decode(const char *filename, char *txt, int size) {
    if (filename == NULL || txt == NULL || size <= 0) {
        return 1;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 2;
    }

    union pixel pixel = {0};
    union bit_character character = {0};
    int fscanf_val = 0;
    unsigned int read_val = 0;

    for (int count = 0; count < size - 1; ++count) {
        for (int i = 0; i < 8; ++i) {
            fscanf_val = fscanf(file, "%u", &read_val);
            if (fscanf_val == 0) {
                fclose(file);
                return 3;
            }
            if (fscanf_val == -1) {
                *(txt + count) = '\0';
                fclose(file);
                return 3;
            }
            pixel.pixel_value = read_val;
            switch (i) {
                case 0: character.bits.b7 = pixel.least_significant; break;
                case 1: character.bits.b6 = pixel.least_significant; break;
                case 2: character.bits.b5 = pixel.least_significant; break;
                case 3: character.bits.b4 = pixel.least_significant; break;
                case 4: character.bits.b3 = pixel.least_significant; break;
                case 5: character.bits.b2 = pixel.least_significant; break;
                case 6: character.bits.b1 = pixel.least_significant; break;
                case 7: character.bits.b0 = pixel.least_significant; break;
                default: break;
            }
        }
        *(txt + count) = character.char_value;
    }

    *(txt + (size > 0 ? size - 1 : 0)) = '\0';
    fclose(file);
    return 0;
}