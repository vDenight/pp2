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

int dll_swap_nodes(struct doubly_linked_list_t* dll, int index) {
    if (dll == NULL || dll_size(dll) < 2) {
        return 1;
    }

    if (index < 0 || index >= dll_size(dll) - 1) {
        return 1;
    }

    struct node_t* n1 = dll_node_at(dll, index);
    struct node_t* n2 = dll_node_at(dll, index + 1);

    if (n1 == NULL || n2 == NULL) {
        return 1;
    }

    struct node_t* n1_prev_node = n1->prev;
    struct node_t* n2_next_node = n2->next;

    if (n1_prev_node != NULL) n1_prev_node->next = n2;
    else dll->head = n2;

    if (n2_next_node != NULL) n2_next_node->prev = n1;
    else dll->tail = n1;

    n2->prev = n1_prev_node;
    n2->next = n1;

    n1->prev = n2;
    n1->next = n2_next_node;

    return 0; // we've done it
}

int dll_comp_nodes(struct doubly_linked_list_t* dll, int index) {
    if (dll == NULL || dll_size(dll) < 2) return 1;
    int val1 = dll_node_at(dll, index)->data;
    int val2 = dll_node_at(dll, index + 1)->data;
    return val1 - val2;
}

int dll_sort_asc(struct doubly_linked_list_t* dll) {
    if (dll == NULL) return 1;

    int size = dll_size(dll);
    if (size == 0) return 1;
    if (size == 1) return 0;

    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size - 1; j++) {
            if (dll_comp_nodes(dll, j) > 0) {
                dll_swap_nodes(dll, j);
            }
        }
    }
    return 0;
}

int dll_sort_desc(struct doubly_linked_list_t* dll) {
    if (dll == NULL) return 1;

    int size = dll_size(dll);
    if (size == 0) return 1;
    if (size == 1) return 0;

    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size - 1; j++) {
            if (dll_comp_nodes(dll, j) < 0) {
                dll_swap_nodes(dll, j);
            }
        }
    }
    return 0;
}