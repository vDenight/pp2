#include <stdio.h>

#include "dictionary.h"

int main(void) {
    struct dictionary_t* my_dict = create_dictionary(2, NULL);

    dictionary_add_word(my_dict, "hello");
    dictionary_display(my_dict);
    dictionary_add_word(my_dict, "hello");
    dictionary_display(my_dict);
    dictionary_add_word(my_dict, "hello");
    dictionary_display(my_dict);

    dictionary_add_word(my_dict, "cw");
    dictionary_display(my_dict);
    dictionary_add_word(my_dict, "cw");
    dictionary_display(my_dict);

    dictionary_add_word(my_dict, "l");
    dictionary_display(my_dict);

    return 0;
}
