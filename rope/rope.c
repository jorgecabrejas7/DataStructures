/**
 * @file rope.c
 * @brief Stub implementation for a Rope data structure for integer sequences.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "rope.h"   // Assuming rope.h is in the same directory or include path is set
#include <stdio.h>  // For printf
#include <stdlib.h> // For NULL
// #include <stdbool.h> // bool is already included via rope.h
// #include <string.h> // Not needed for these integer-based stubs

Rope* rope_create() {
    printf("STUB: rope_create not implemented\n");
    return NULL;
}

Rope* rope_create_from_array(const int* initial_elements, int count) {
    printf("STUB: rope_create_from_array not implemented\n");
    (void)initial_elements; // Parameter unused in stub
    (void)count;            // Parameter unused in stub
    return NULL;
}

void rope_destroy(Rope* rope) {
    printf("STUB: rope_destroy not implemented\n");
    (void)rope; // Parameter unused in stub
}

int rope_get_length(const Rope* rope) {
    printf("STUB: rope_get_length not implemented\n");
    (void)rope; // Parameter unused in stub
    return 0;
}

int rope_get_element_at(const Rope* rope, int index, bool* success) {
    printf("STUB: rope_get_element_at not implemented\n");
    (void)rope;  // Parameter unused in stub
    (void)index; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

Rope* rope_concatenate(Rope* r1, Rope* r2) {
    printf("STUB: rope_concatenate not implemented\n");
    (void)r1; // Parameter unused in stub
    (void)r2; // Parameter unused in stub
    return NULL;
}

bool rope_split(Rope* r, int k, Rope** left_rope_ptr, Rope** right_rope_ptr) {
    printf("STUB: rope_split not implemented\n");
    (void)r; // Parameter unused in stub
    (void)k; // Parameter unused in stub
    if (left_rope_ptr) {
        *left_rope_ptr = NULL;
    }
    if (right_rope_ptr) {
        *right_rope_ptr = NULL;
    }
    return false;
}

void rope_print_debug(const Rope* rope, int mode) {
    printf("STUB: rope_print_debug not implemented\n");
    (void)rope; // Parameter unused in stub
    (void)mode; // Parameter unused in stub
}
