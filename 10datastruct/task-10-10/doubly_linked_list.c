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
        dll->tail = new_node;
    }

    return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value) {
    if (!dll) return 1;

    struct node_t* new_node = calloc(1, sizeof(struct node_t));
    if (!new_node) return 2;

    new_node->data = value;

    if (dll->head == NULL) { // list is empty case
        dll->tail = new_node;
        dll->head = new_node;
    } else {
        new_node->next = dll->head;
        dll->head = new_node;
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
        return val;
    }
    // more elem list
    int val = (dll->head)->data;
    struct node_t* new_head = (dll->head)->next;
    free(dll->head);
    dll->head = new_head;
    return val;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->tail == NULL) {if (err_code) *err_code = 1; return 0;}
    if (dll->head == dll->tail) { // one elem list
        struct node_t* popped = dll->head;
        dll->head = NULL;
        dll->tail = NULL;
        int val = popped->data;
        free(popped);
        return val;
    }
    // more elem list
    int val = (dll->tail)->data;
    struct node_t* new_tail = (dll->tail)->prev;
    free(dll->tail);
    dll->tail= new_tail;
    return val;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->head == NULL) {if (err_code) *err_code = 1; return 0;}
    if (err_code) *err_code = 0;
    return (dll->head)->data;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->tail == NULL) {if (err_code) *err_code = 1; return 0;}
    if (err_code) *err_code = 0;
    return (dll->tail)->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL) return NULL;
    return (dll->head);
}

struct node_t* dll_end(struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->tail == NULL) return NULL;
    return (dll->tail);
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

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if (dll == NULL) { if (err_code) *err_code = 1; return 0;}
    if (index >= (unsigned int) dll_size(dll)) { if (err_code) *err_code = 1; return 0;}

    struct node_t* current = dll->head;
    for (unsigned int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
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

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value) {
    if (dll == NULL) return 1;
    if (index > (unsigned int) dll_size(dll)) return 1;

    struct node_t* new_node = calloc(1, sizeof(struct node_t));
    if (!new_node) return 2;
    new_node->data = value;

    if (index == 0) {
        dll_push_front(dll, value);
    }
    if (index == dll_size(dll)) {
        dll_push_back(dll, value);
    }

    struct node_t* prev = dll_node_at(dll, index - 1);
    struct node_t* next = dll_node_at(dll, index);

    new_node->prev = prev;
    prev->next = new_node;

    new_node->next = next;
    next->prev = new_node;

    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if (dll == NULL) {if (err_code) *err_code = 1; return 0;}
    if (index >= (unsigned int) dll_size(dll)) {if (err_code) *err_code = 1; return 0;}

    if (index == 0) {
        return dll_pop_front(dll, NULL);
    }
    if (index == (dll_size(dll) - 1)) {
        return dll_pop_back(dll, NULL);
    }

    struct node_t* pop = dll_node_at(dll, index);
    struct node_t* prev = dll_node_at(dll, index - 1);
    struct node_t* next = dll_node_at(dll, index + 1);

    prev->next = next;
    next->prev = prev;

    int val = pop->data;
    free(pop);
    return val;
}

void dll_clear(struct doubly_linked_list_t* dll) {
    if (dll == NULL) return;
    int err_code = 0;
    while (!err_code) {
        dll_pop_front(dll, &err_code);
    }
    free(dll);
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
