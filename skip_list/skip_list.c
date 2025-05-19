/**
 * @file skip_list.c
 * @brief Stub implementation for a Skip List.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "skip_list.h" // Assuming skip_list.h is in the same directory or include path is set
#include <stdio.h>     // For printf
#include <stdlib.h>    // For NULL
// #include <stdbool.h> // bool is already included via skip_list.h
// #include <limits.h>  // Not strictly needed for these stubs

// Corrected signature to match .h (no parameters)
SkipList* skip_list_create() {
    printf("STUB: skip_list_create not implemented\n");
    return NULL;
}

void skip_list_destroy(SkipList* sl) {
    printf("STUB: skip_list_destroy not implemented\n");
    (void)sl; // Parameter unused in stub
}

bool skip_list_insert(SkipList* sl, int value) {
    printf("STUB: skip_list_insert not implemented\n");
    (void)sl;    // Parameter unused in stub
    (void)value; // Parameter unused in stub
    return false; // As per .h: "false if the value was already present or if memory allocation failed"
}

bool skip_list_contains(const SkipList* sl, int value) {
    printf("STUB: skip_list_contains not implemented\n");
    (void)sl;
    (void)value;
    return false;
}

bool skip_list_remove(SkipList* sl, int value) {
    printf("STUB: skip_list_remove not implemented\n");
    (void)sl;
    (void)value;
    return false;
}

// Corrected return type to int as per .h file
int skip_list_size(const SkipList* sl) {
    printf("STUB: skip_list_size not implemented\n");
    (void)sl;
    return 0;
}

bool skip_list_is_empty(const SkipList* sl) {
    printf("STUB: skip_list_is_empty not implemented\n");
    (void)sl;
    return true;
}

void skip_list_print(const SkipList* sl) {
    printf("STUB: skip_list_print not implemented\n");
    (void)sl;
}

// The random_level helper from the original stub is an internal detail
// and not part of the public API, so it's omitted here.