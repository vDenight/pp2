//
// Created by mcihal on 08.06.25.
//
#include "doubly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

struct doubly_linked_list_t* dll_create() {
    struct doubly_linked_list_t* new_dll = calloc(1, sizeof(struct doubly_linked_list_t));
    if (!new_dll) return NULL;
    return new_dll;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value) {
    if (!dll) return 1;

    struct node_t* new_node = calloc(1, sizeof(struct node_t));
    if (!new_node) return 2;

    new_node->data = value;

    if (dll->tail == NULL) { // list is empty case
        dll->tail = new_node;
        dll->head = new_node;
    } else {
        new_node->prev = dll->tail;
        (dll->tail)->next = new_node;
        dll->tail = new_node;
    }

    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->head == NULL) {if (err_code) *err_code = 1; return 0;}
    if (dll->head == dll->tail) { // one elem list
        struct node_t* popped = dll->head;
        dll->head = NULL;
        dll->tail = NULL;
        int val = popped->data;
        free(popped);
        if (err_code) *err_code = 0;
        return val;
    }
    // more elem list
    int val = (dll->head)->data;
    struct node_t* new_head = (dll->head)->next;
    free(dll->head);
    new_head->prev = NULL;
    dll->head = new_head;

    if (err_code) *err_code = 0;
    return val;
}

int dll_size(const struct doubly_linked_list_t* dll) {
    if (dll == NULL) return -1;
    int size = 0;
    struct node_t* current = dll->head;
    while (current) {
        size++;
        current = current->next;
    }
    return size;
}

int dll_is_empty(const struct doubly_linked_list_t* dll) {
    if (dll == NULL) return -1;
    if (dll_size(dll) == 0) return 1;
    return 0;
}

struct node_t* dll_node_at(const struct doubly_linked_list_t* dll, unsigned int index) {
    if (dll == NULL) { return NULL;}
    if (index >= (unsigned int) dll_size(dll)) { return NULL;}

    struct node_t* current = dll->head;
    for (unsigned int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void dll_clear(struct doubly_linked_list_t* dll) {
    if (dll == NULL) return;
    int err_code = 0;
    while (!err_code) {
        dll_pop_front(dll, &err_code);
    }
}

void dll_display(const struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL) return;

    struct node_t* current = dll->head;

    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
}

void dll_display_reverse(const struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->tail== NULL) return;

    struct node_t* current = dll->tail;

    while (current) {
        printf("%d ", current->data);
        current = current->prev;
    }
}

void dll_put_node(struct doubly_linked_list_t* dll, int index, struct node_t* node) {
    if (index == 0) {
        if (dll_is_empty(dll)) {
            dll->head = node;
            dll->tail = node;
            node->next = NULL;
            node->prev = NULL;
            return;
        }
        node->prev = NULL;
        node->next = dll->head;
        (dll->head)->prev = node;
        dll->head = node;
        return;
    }

    if (index == dll_size(dll)) {
        node->next = NULL;
        node->prev = dll->tail;
        (dll->tail)->next = node;
        dll->tail = node;
        return;
    }

    struct node_t* prev = dll_node_at(dll, index - 1);
    struct node_t* next = dll_node_at(dll, index);
    if (prev == NULL || next == NULL) return;

    prev->next = node;
    node->prev = prev;

    next->prev = node;
    node->next = next;
    // done
}

struct node_t* pop_node(struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL) return NULL; // dll->head == NULL instead of is_empty because clang throws an error

    struct node_t* temp = dll->head;
    struct node_t* new_head = temp->next;
    if (new_head == NULL) {
        dll->tail = NULL;
    }
    dll->head = new_head;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}


int dll_concat_zip(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2) {
    if (dll1 == NULL || dll2 == NULL) return 1;

    int dll1_innit_size = dll_size(dll1);

    for (int i = 0; i < dll1_innit_size; i++) {
        int index = i * 2 + 1;
        struct node_t* popped = pop_node(dll2);
        if (popped == NULL) return 0;
        dll_put_node(dll1, index, popped);
    }

    while (!dll_is_empty(dll2)) {
        struct node_t* popped = pop_node(dll2);
        dll_put_node(dll1, dll_size(dll1), popped);
    }
    return 0;
}

int dll_concat_begin(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2) {
    if (dll1 == NULL || dll2 == NULL) return 1;

    struct node_t* popped;
    int index = 0;

    while ((popped = pop_node(dll2))) {
        dll_put_node(dll1, index, popped);
        index++;
    }
    return 0;
}

int dll_concat_end(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2) {
    if (dll1 == NULL || dll2 == NULL) return 1;

    struct node_t* popped;

    while ((popped = pop_node(dll2))) {
        dll_put_node(dll1, dll_size(dll1), popped);
    }
    return 0;
}
