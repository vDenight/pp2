#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int main() {
    struct circular_buffer_t *cb = NULL;
    int capacity = 5;
    int err_code;
    int value;

    printf("--- Testing circular_buffer_create_struct ---\n");
    if (circular_buffer_create_struct(&cb, capacity) == 0) {
        printf("Circular buffer created with capacity %d.\n", capacity);
        // Expected Output: Circular buffer created with capacity 5.
    } else {
        printf("Failed to create circular buffer.\n");
    }

    printf("\n--- Testing circular_buffer_empty ---\n");
    printf("Is buffer empty? %s\n", circular_buffer_empty(cb) == 0 ? "Yes" : "No");
    // Expected Output: Is buffer empty? Yes

    printf("\n--- Testing circular_buffer_push_back ---\n");
    for (int i = 1; i <= 3; ++i) {
        printf("Pushing back: %d\n", i);
        // Expected Output: Pushing back: 1
        // Expected Output: Pushing back: 2
        // Expected Output: Pushing back: 3
        circular_buffer_push_back(cb, i);
        circular_buffer_display(cb);
    }
    printf("Is buffer empty? %s\n", circular_buffer_empty(cb) == 0 ? "Yes" : "No");
    // Expected Output: Is buffer empty? No
    printf("Is buffer full? %s\n", circular_buffer_full(cb) == 1 ? "Yes" : "No");
    // Expected Output: Is buffer full? No
    printf("Buffer contents: ");
    circular_buffer_display(cb);
    // Expected Output: Buffer contents: 1 2 3

    printf("\n--- Testing circular_buffer_pop_front ---\n");
    value = circular_buffer_pop_front(cb, &err_code);
    if (err_code == 0) {
        printf("Popped front: %d\n", value);
        // Expected Output: Popped front: 1
    } else {
        printf("Failed to pop front (error code: %d)\n", err_code);
    }
    printf("Buffer contents after pop: ");
    circular_buffer_display(cb);
    // Expected Output: Buffer contents after pop: 2 3

    printf("\n--- Testing circular_buffer_push_back to fill ---\n");
    for (int i = 4; i <= 6; ++i) {
        printf("Pushing back: %d\n", i);
        // Expected Output: Pushing back: 4
        // Expected Output: Pushing back: 5
        // Expected Output: Pushing back: 6
        circular_buffer_push_back(cb, i);
    }
    printf("Is buffer full? %s\n", circular_buffer_full(cb) == 1 ? "Yes" : "No");
    // Expected Output: Is buffer full? Yes
    printf("Buffer contents: ");
    circular_buffer_display(cb);
    // Expected Output: Buffer contents: 2 3 4 5 6

    printf("\n--- Testing circular_buffer_pop_back ---\n");
    value = circular_buffer_pop_back(cb, &err_code);
    if (err_code == 0) {
        printf("Popped back: %d\n", value);
        // Expected Output: Popped back: 6
    } else {
        printf("Failed to pop back (error code: %d)\n", err_code);
    }
    printf("Buffer contents after pop: ");
    circular_buffer_display(cb);
    // Expected Output: Buffer contents after pop: 2 3 4 5

    printf("\n--- Testing emptying the buffer ---\n");
    while (circular_buffer_empty(cb) != 0) {
        value = circular_buffer_pop_front(cb, &err_code);
        if (err_code == 0) {
            printf("Popped front: %d\n", value);
            // Expected Output: Popped front: 2
            // Expected Output: Popped front: 3
            // Expected Output: Popped front: 4
            // Expected Output: Popped front: 5
        }
    }
    printf("Is buffer empty? %s\n", circular_buffer_empty(cb) == 0 ? "Yes" : "No");
    // Expected Output: Is buffer empty? Yes

    printf("\n--- Testing pushing after emptying (wrapping around) ---\n");
    circular_buffer_push_back(cb, 10);
    printf("Pushing back: 10\n");
    // Expected Output: Pushing back: 10
    circular_buffer_push_back(cb, 20);
    printf("Pushing back: 20\n");
    // Expected Output: Pushing back: 20
    printf("Buffer contents after pushing: ");
    circular_buffer_display(cb);
    // Expected Output: Buffer contents after pushing: 10 20

    printf("\n--- Testing filling the buffer and pushing again (overwrite) ---\n");
    for (int i = 1; i <= capacity; ++i) {
        printf("Pushing back: %d\n", i * 10);
        // Expected Output: Pushing back: 10
        // Expected Output: Pushing back: 20
        // Expected Output: Pushing back: 30
        // Expected Output: Pushing back: 40
        // Expected Output: Pushing back: 50
        circular_buffer_push_back(cb, i * 10);
    }
    printf("Buffer contents when full: ");
    circular_buffer_display(cb);
    // Expected Output: Buffer contents when full: 10 20 30 40 50
    printf("Is buffer full? %s\n", circular_buffer_full(cb) == 1 ? "Yes" : "No");
    // Expected Output: Is buffer full? Yes
    circular_buffer_push_back(cb, 100);
    printf("Pushing back: 100\n");
    // Expected Output: Pushing back: 100
    printf("Pushed back 100 (should overwrite front). Buffer contents: ");
    circular_buffer_display(cb);
    // Expected Output: Pushed back 100 (should overwrite front). Buffer contents: 100 20 30 40 50

    printf("\n--- Testing popping all elements ---\n");
    while (circular_buffer_empty(cb) != 0) {
        value = circular_buffer_pop_front(cb, &err_code);
        if (err_code == 0) {
            printf("Popped front: %d\n", value);
            // Expected Output: Popped front: 100
            // Expected Output: Popped front: 20
            // Expected Output: Popped front: 30
            // Expected Output: Popped front: 40
            // Expected Output: Popped front: 50
        }
    }
    printf("Is buffer empty? %s\n", circular_buffer_empty(cb) == 0 ? "Yes" : "No");
    // Expected Output: Is buffer empty? Yes

    printf("\n--- Testing destroy ---\n");
    circular_buffer_destroy_struct(&cb);
    printf("Circular buffer destroyed.\n");
    // Expected Output: Circular buffer destroyed.

    return 0;
}