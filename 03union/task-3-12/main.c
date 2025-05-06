#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "steganography.h"

void read_mess(char* buffer);

int main(void) {

    char message[1001];
    char input_filename[30];
    char output_filename[30];
    char option;
    char c;
    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    scanf("%c", &option);

    scanf("%c", &c);
    if (c != '\n') {
        printf("Incorrect input data");
        return 1;
    }

    switch (toupper(option)) {

        case 'E':
            printf("Enter a message to be encoded: ");
            read_mess(message);

            printf("Enter input file name: ");
            scanf("%29s", input_filename);

            printf("Enter output file name: ");
            scanf("%29s", output_filename);

            switch (encode(input_filename, message, output_filename)) {
                case 0:
                    printf("File saved");
                    return 0;
                case 2:
                    printf("Couldn't open file");
                    return 4;
                case 3:
                    printf("File corrupted");
                    return 6;
                case 4:
                    printf("Couldn't create file");
                    return 5;
                default:
                    return 2137;
            }

        case 'D':

            printf("Enter input file name: ");
            scanf("%29s", input_filename);

            switch (decode(input_filename, message, 1001)) {
                case 0:
                    printf("%s", message);
                    return 0;
                case 2:
                    printf("Couldn't open file");
                    return 4;
                case 3:
                    printf("File corrupted");
                    return 6;
                default:
                    return 2137;
            }

        default:
            printf("Incorrect input data");
            return 1;
    }
}

void read_mess(char* buffer) {
    char c;
    int count = 0;
    while ((c = getchar()) != '\n') {
        if (count < 1000) {
            *(buffer + count) = c;
            count++;
        }
    }

    *(buffer + count) = '\0';
}

/*
Przygotuj funkcje do kodowania i odkodowywania wiadomosci w obrazach.
    Obraz bedzie zapisany w postaci tekstowej, kazdy wiersz w pliku to jeden wiersz obrazu.
    Obrazy beda w odcieniach szarosci, wartosci pikseli beda w zakresie 0-255.

    Wiadomosc ma byc zakodowana na ostatnim bicie kazdego piksela.
    Oznacza to, ze aby odczytac jeden znak wiadomosci konieczne bedzie przeanalizowanie 8 kolejnych pikseli (tutaj bajto
w) obrazu wejsciowego.

    Funkcje powinny miec nastepujace prototypy:

    int encode(const char *input, char *txt, const char *output)

    Funkcja ma za zadanie zakodowac wiadomosc przekazana w parametrze txt w obrazie,
    ktorego nazwa zostanie przekazana w parametrze input.
    Obraz z ukryta wiadomoscia ma zostac zapisany do pliku o nazwie przekazanej parametrem output.

    Jezeli tresc wiadomosci bedzie krotsza niz maksymalna dopuszczalna dla danego obrazy to najmlodsze bity w pozostalyc
h pikselach powinna zostac wyzerowane.

    Funkcja encode powinna zwrocic wartosc:
     3 - jezeli niemozliwe bedzie zakodowania calej wiadomosci w pliku,
     4 - jezeli nie uda sie utworzyc pliku wyjsciowego,
     2 - jezeli plik wejsciowy nie bedzie istanial,
     1 - w przypadku blednych danych przekazanych podczas wywolywania funkcji encode,
     0 - w przypadku sukcesu.


    int decode(const char * filename, char *txt, int size)

    Funkcja ma odczytac wiadomosc ukryta w pliku o nazwie przekazanej w parametrze filename i zapisac ja do zmiennej txt
.
    Parametr size oznacza pojemnosc tablicy txt w bajtach.

    Funkcja ma zwrocic:
     3 - jezeli dane w pliku wejsciowym beda uszkodzone,
     1 - w przypadku blednych danych wejsciowych,
     2 - kiedy nie uda sie otworzyc pliku wejsciowego,
     0 - w przypadku sukcesu.

    Napisz program, ktory pozwoli uzytkownikowi ukrywac wiadomosc w obrazie i odczytywac wiadomosc z obrazu.

    Wpisanie litery e/E bedzie oznaczalo, ze uzytkownik chce ukryc tekst w obrazie, wtedy program ma pobrac tekst
    do ukrycia (nie wiecej niz 1000 znakow) oraz nazwe pliku z obrazem i nazwe pliku wyjsciowego (nie przekrocza 29 znak
ow).

    Program powinien wyswietlic komunikat:
    - File saved w przypadku powodzenia (kod bledu 0),
    - Couldn't open file - jezeli plik wejsciowy nie zostanie odnaleziony (kod bledu 4).
    - Couldn't create file - jezeli nie mozliwe bedzie utworzenie pliku wyjsciowego (kod bledu 5),
    - File corrupted - jezeli nie uda sie zapisac wiadomosci w pliku (kod bledu 6).

    Wpisanie przez uzytkownika litery d/D bedzie oznaczalo, ze chce on odczytac wiadomosc ukryta w pliku.
    Program powinien zapytac sie uzytkownika o nazwe pliku a nastepnie wyswietlic odczytana wiadomosc i zakonczyc sie z

    kodem bledu 0.

    Program powinien wyswietlic komunikat:
    - Couldn't open file - jezeli nie uda sie otworzyc pliku zrodlowego (kod bledu 4)
    - File corrupted - jezeli nie uda sie odczytac wiadomosci z pliku (kod bledu 6).

    W przypadku podania przez uzytkownika blednego znaku program powinien wyswietlic komunikat Incorrect input data i za
kocznyc dzialanie z kodem bledu 1.
*/