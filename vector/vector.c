/**
 * @file vector.c
 * @brief Stub implementation for a dynamic array (Vector) of integers.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "vector.h" // Assuming vector.h is in the same directory or include path is set
#include <stdio.h>  // For printf
#include <stdlib.h> // For NULL
// #include <stdbool.h> // bool is already included via vector.h
// #include <string.h> // Not needed for these stubs


/**
 * @brief Creates a new, empty vector with a specified initial capacity for int elements.
 *
 * If initial_capacity is 0, the internal data pointer will be NULL initially. Memory
 * will be allocated upon the first addition of an element or explicit reservation.
 *
 * @param initial_capacity The initial number of int elements the vector can hold.
 *                         Must be a non-negative integer.
 * @return Vector* A pointer to the newly created Vector structure, or NULL if
 *                 memory allocation fails or if initial_capacity is negative.
 * @note The caller is responsible for eventually calling vector_destroy() on the
 *       returned vector to free its resources.
 */

Vector* vector_create(int initial_capacity) {
    if (initial_capacity < 0) return NULL;

    Vector* v = malloc(sizeof(Vector));

    if (v == NULL) return NULL;

    v->capacity = initial_capacity;
    v->size = 0;
    v->data = NULL;
    
    if (initial_capacity == 0) return v;
    v->data = malloc(initial_capacity * sizeof(int));
    if (v->data == NULL){
        free(v);
        return NULL;
    }
    return v;

}

void vector_destroy(Vector* vec) {
    printf("STUB: vector_destroy not implemented\n");
    (void)vec; // Parameter unused in stub
}

// Corrected return type to int
int vector_size(const Vector* vec) {
    printf("STUB: vector_size not implemented\n");
    (void)vec;
    return 0;
}

// Corrected return type to int
int vector_capacity(const Vector* vec) {
    printf("STUB: vector_capacity not implemented\n");
    (void)vec;
    return 0;
}

bool vector_is_empty(const Vector* vec) {
    printf("STUB: vector_is_empty not implemented\n");
    (void)vec;
    return true;
}

bool vector_push_back(Vector* vec, int item) {
    printf("STUB: vector_push_back not implemented\n");
    (void)vec;  // Parameter unused in stub
    (void)item; // Parameter unused in stub
    return false;
}

// Corrected signature to match .h (vector_get_item)
int vector_get_item(const Vector* vec, int index, bool* success) {
    printf("STUB: vector_get_item not implemented\n");
    (void)vec;   // Parameter unused in stub
    (void)index; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected signature to match .h (vector_set_item)
bool vector_set_item(Vector* vec, int index, int item) {
    printf("STUB: vector_set_item not implemented\n");
    (void)vec;
    (void)index;
    (void)item;
    return false;
}

// Corrected signature to match .h (vector_insert_item)
bool vector_insert_item(Vector* vec, int index, int item) {
    printf("STUB: vector_insert_item not implemented\n");
    (void)vec;
    (void)index;
    (void)item;
    return false;
}

// Corrected signature to match .h (vector_pop_back)
int vector_pop_back(Vector* vec, bool* success) {
    printf("STUB: vector_pop_back not implemented\n");
    (void)vec;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected signature to match .h (vector_remove_item)
bool vector_remove_item(Vector* vec, int index) {
    printf("STUB: vector_remove_item not implemented\n");
    (void)vec;
    (void)index;
    return false;
}

void vector_clear(Vector* vec) {
    printf("STUB: vector_clear not implemented\n");
    (void)vec;
}

// Corrected parameter type to int
bool vector_reserve(Vector* vec, int new_capacity) {
    printf("STUB: vector_reserve not implemented\n");
    (void)vec;
    (void)new_capacity;
    return false;
}

bool vector_shrink_to_fit(Vector* vec) {
    printf("STUB: vector_shrink_to_fit not implemented\n");
    (void)vec;
    return false;
}
