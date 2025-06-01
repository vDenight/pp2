//
// Created by mcihal on 01.06.25.
//

#ifndef EASTER_H
#define EASTER_H

void print_chicken();
void print_egg();
void print_rabbit();

void (**easter(int size, void(*)(void), void(*)(void), void(*)(void)))(void);

#endif //EASTER_H
