//
// Created by mcihal on 08.06.25.
//

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

struct doubly_linked_list_t
{
    struct node_t *head;
    struct node_t *tail;
};

struct node_t
{
    int data;
    struct node_t *next;
    struct node_t *prev;
};

struct doubly_linked_list_t* dll_create();

int dll_push_back(struct doubly_linked_list_t* dll, int value);
int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code);

int dll_size(const struct doubly_linked_list_t* dll);
int dll_is_empty(const struct doubly_linked_list_t* dll);

void dll_clear(struct doubly_linked_list_t* dll);

void dll_display(const struct doubly_linked_list_t* dll);
void dll_display_reverse(const struct doubly_linked_list_t* dll);

int dll_concat_zip(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2);
int dll_concat_begin(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2);
int dll_concat_end(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2);

#endif //DOUBLY_LINKED_LIST_H
