//
// Created by mcihal on 27.05.25.
//

#ifndef POINT_H
#define POINT_H

struct point_t {
    int x;
    int y;
};

struct point_t* set(struct point_t* p, int x, int y);
void show(const struct point_t* p);
struct point_t* read(struct point_t* p);
float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);

#endif //POINT_H
