/**
 * @file binary_heap.c
 * @brief Stub implementation for an array-based Binary Min-Heap.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "binary_heap.h" // Assuming binary_heap.h is in the same directory or include path is set
#include <stdio.h>      // For printf
#include <stdlib.h>     // For NULL (though not strictly needed for stubs returning NULL)

BinaryHeap* binary_heap_create(int initial_capacity) {
    printf("STUB: binary_heap_create not implemented\n");
    (void)initial_capacity; // Parameter unused in stub
    return NULL;
}

void binary_heap_destroy(BinaryHeap* heap) {
    printf("STUB: binary_heap_destroy not implemented\n");
    (void)heap; // Parameter unused in stub
}

bool binary_heap_insert(BinaryHeap* heap, int value) {
    printf("STUB: binary_heap_insert not implemented\n");
    (void)heap;  // Parameter unused in stub
    (void)value; // Parameter unused in stub
    return false;
}

int binary_heap_extract_min(BinaryHeap* heap, bool* success) {
    printf("STUB: binary_heap_extract_min not implemented\n");
    (void)heap; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return for int, actual value meaningless if success is false
}

int binary_heap_peek_min(const BinaryHeap* heap, bool* success) {
    printf("STUB: binary_heap_peek_min not implemented\n");
    (void)heap; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return for int, actual value meaningless if success is false
}

bool binary_heap_is_empty(const BinaryHeap* heap) {
    printf("STUB: binary_heap_is_empty not implemented\n");
    (void)heap; // Parameter unused in stub
    return true;
}

int binary_heap_size(const BinaryHeap* heap) {
    printf("STUB: binary_heap_size not implemented\n");
    (void)heap; // Parameter unused in stub
    return 0;
}

int binary_heap_capacity(const BinaryHeap* heap) {
    printf("STUB: binary_heap_capacity not implemented\n");
    (void)heap; // Parameter unused in stub
    return 0;
}

void binary_heap_clear(BinaryHeap* heap) {
    printf("STUB: binary_heap_clear not implemented\n");
    (void)heap; // Parameter unused in stub
}

void binary_heap_print_array(const BinaryHeap* heap) {
    printf("STUB: binary_heap_print_array not implemented\n");
    (void)heap; // Parameter unused in stub
}