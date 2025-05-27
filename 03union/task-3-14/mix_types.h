//
// Created by mcihal on 27.05.25.
//

#ifndef MIX_TYPES_H
#define MIX_TYPES_H

enum type_t{
    INTEGER,
    DOUBLE,
    CHARACTER
  };

struct data_t
{
    enum type_t type;
    union {
        int i;
        double d;
        char c;
    };
};

int sort(struct data_t *data[], int size);
void display(struct data_t *data[], int size);
int read_mix_type(struct data_t* element);

enum read_code {
    READ_CORRUPTED_DATA = -1,
    READ_OK = 0,
    READ_FINISHED = 1
};

#endif //MIX_TYPES_H
