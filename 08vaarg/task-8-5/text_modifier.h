//
// Created by mrybczynski on 6/4/2025.
//

#ifndef TEXT_MODIFIER_H
#define TEXT_MODIFIER_H

char** text_modifier(const char* text, int N, ...);

char* lower_to_upper(const char *in);
char* upper_to_lower(const char *in);
char* space_to_dash(const char *in);
char* reverse_letter(const char *in);

#endif //TEXT_MODIFIER_H
